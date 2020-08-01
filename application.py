import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from flask import url_for

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # SYMBOL | NAME | SHARES | CURRENT PRICE | TOTAL VALUE ( shares * price)

    user_id=session["user_id"]

    # List of stocks
    rows = db.execute("SELECT symbol, SUM(shares), price, name FROM portfolio WHERE user_id=:user_id GROUP BY symbol", user_id=user_id)

    # Get cash balance
    cash_rows = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
    cash_balance = cash_rows[0]["cash"]

    # Total value of all shares + cash holdings
    total_value = cash_balance

    # Get total value shares for each stock
    for row in rows:
        # Add row "value" to rows and set it to the value of shares * price
        row["value"] = row["SUM(shares)"] * row["price"]
        total_value +=row["value"]

    return render_template("index.html", rows=rows, total_value=usd(total_value), cash_balance=usd(cash_balance))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        # Lookup stock price
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # Return error if stock is not found
        if not quote:
            return apology("Stock not found")

        else:
            # Render an apology if the input is not a positive integer.
            shares = int(request.form.get("shares"))

            if shares < 1:
                return apology("Please enter a positive integer")

            # SELECT how much cash the user currently has in users
            row = db.execute("SELECT cash FROM USERS WHERE id = :id", id=session["user_id"])
            cash = float(row[0]["cash"])

            shareprice = quote['price']
            totalprice = shares * shareprice

            # Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
            if totalprice > cash:
                return apology("You can't afford that many shares")

            # Store transaction records in database. Username, Stock, Shares, Price. Date and time is recorded automatically in database
            db.execute("INSERT INTO portfolio (user_id, symbol, name, shares, price) VALUES (:user_id, :symbol, :name, :shares, :price)",
                    user_id = session['user_id'],
                    symbol = quote['symbol'],
                    name = quote['name'],
                    shares=shares,
                    price=shareprice)

            new_balance = cash - totalprice

            # Update cash holdings
            db.execute("UPDATE users SET cash = :new_balance WHERE id = :id ", new_balance=new_balance, id=session['user_id'])

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.
    if request.method == "GET":
        return render_template("quote.html")

    #Submit the user’s input via POST to /quote.
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # Return error if stock is not found
        if not quote:
            return apology("Stock not found")
        return render_template("quoted.html", quote=quote)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Display register.html if user is not registered
    if request.method == "GET":
        return render_template("register.html")

    # Get input from form and add to database
    else:
        username = request.form.get("username")
        password = request.form.get("password")

        # Look for username in database
        check = db.execute("SELECT * FROM users WHERE username =:username",username=username)

        # If username does not exist already, add new user to database
        if not check:
            hash_pwd = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)",username,hash_pwd)

            #Return to login page
            flash('You were successfully registered!')

            return render_template("login.html")

        else:
            return apology("Username already in use")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id=session["user_id"]

    # SELECT stocks that user owns
    symbol = db.execute("SELECT symbol, shares FROM portfolio WHERE user_id=:user_id", user_id=user_id)

    if request.method == "GET":
        return render_template("sell.html", symbol=symbol)

    else:
        sell_symbol = request.form.get("symbol")
        sell_shares = int(request.form.get("shares"))

        if not sell_symbol:
            return apology("Missing symbol")

        if not sell_shares:
            return apology("Missing shares")

        # Render apology if user does not have that many stocks in portfolio
        shares_rows = db.execute("SELECT shares FROM portfolio WHERE user_id=:user_id AND symbol =:symbol", user_id=user_id, symbol=sell_symbol)
        shares_owned = shares_rows[0]["shares"]

        if sell_shares > shares_owned:
            return apology("Too many shares")

        new_total = ???
        # Update portfolio
        db.execute("UPDATE ")

UPDATE portfolio
SET column1 = value1, column2 = value2, ...
WHERE condition;
    return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
