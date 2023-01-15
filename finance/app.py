import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


def is_integer(n):
    try:
        float(n)
    except ValueError:
        return False
    else:
        return float(n).is_integer()


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Extract Portfolio Data for Each user

    portfolio = db.execute("SELECT symbol,SUM(shares) FROM history WHERE user_id IS ? GROUP BY symbol", session.get("user_id"))
    print(portfolio)

    # Loop over each element in the list and append relevant values - Name & Price
    summation = 0
    index_l = []
    index = 0
    for dict_element in portfolio:
        dict = lookup(dict_element["symbol"])
        dict_element["name"] = dict["name"]
        dict_element["price"] = dict["price"]
        dict_element["total"] = int(dict_element["SUM(shares)"]) * float(dict_element["price"])
        summation += dict_element["total"]
        # Check if Zero Valued
        if (int(dict_element["SUM(shares)"]) == 0):
            index_l.append(index)

        index += index

    # Remove Zero valued stocks
    for x in index_l:
        portfolio.pop(x)

    # Get the users cash balance

    total = db.execute("SELECT cash FROM users WHERE id IS ?", session.get("user_id"))

    # Sum Total
    print(total)
    cash = total[0]["cash"]
    print(cash)
    summation += cash

    # Export

    return render_template("index.html", portfolio=portfolio, cash=cash, summation=summation)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure shares were submitted
        if (is_integer(request.form.get("shares")) == False):
            return apology("must provide shares number greater than zero, non-decimal", 400)

        # Ensure shares were submitted
        if not (request.form.get("shares")) or (int(request.form.get("shares")) <= 0):
            return apology("must provide shares number greater than zero, non-decimal", 400)

        # Get the values
        symbol = request.form.get("symbol")
        dict = lookup(symbol)
        if (dict == None):
            return apology("symbol doesnt exist", 400)

        shares = int(request.form.get("shares"))
        price = float(dict["price"])

        # Adjust cash of user
        # print(session.get("user_id"))
        pre_trade_cash = db.execute("SELECT cash FROM users WHERE id IS ?", session.get("user_id"))
        pre_trade_cash = float(pre_trade_cash[0]["cash"])
        # print(pre_trade_cash)
        post_trade_cash = pre_trade_cash - (price * shares)
        # print(post_trade_cash)

        # Create time element
        now = datetime.now()

        if post_trade_cash >= 0:
            # Update cash value
            db.execute("UPDATE users SET cash = ? WHERE id IS ?", post_trade_cash, session.get("user_id"))
            # Add transaction to ledger
            db.execute("INSERT INTO history (user_id, shares, symbol, price, time) VALUES(?,?,?,?,?)",session.get("user_id"), shares, symbol, price, now.strftime("%d/%m/%Y %H:%M:%S"))
        else:
            return apology("your balance is not sufficient to complete this transaction", 400)

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # Get Transaction History

    transactions = db.execute("SELECT symbol, shares, price, time FROM history WHERE user_id IS ?", session.get("user_id"))

    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    if request.method == "POST":
        if (request.form.get("symbol") == ""):
            return apology("input cannot be blank", 400)

        dict = lookup(request.form.get("symbol"))

        if (dict == None):
            return apology("symbol doesnt exist", 400)

        return render_template("quoted.html", name=dict["name"], price=usd(dict["price"]), symbol=dict["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Get Input first
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirmation = request.form.get("confirmation")
        print("Username is:" + username)

        # Validate Input
        if (username == "" or password == "" or password_confirmation == ""):
            return apology("either input is blank or the passwords do not match", 400)

        if (password != password_confirmation):
            return apology("either input is blank or the passwords do not match", 400)

        # Validate if user name exists
        existing_users = db.execute("SELECT username FROM users")
        for dict_element in existing_users:
            if (username == dict_element["username"]):
                return apology("That username is already in use", 400)

        hash = generate_password_hash(password)
        # Send Output to Database
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, hash)

        # Confirm Registration
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # Extract Portfolio Data for that particular share

        portfolio = db.execute("SELECT SUM(shares) FROM history WHERE user_id IS ? AND symbol IS ? GROUP BY symbol", session.get("user_id"), request.form.get("symbol"))
        print(portfolio)

        # Validate Amount Being Sold

        if (int(request.form.get("shares")) > int(portfolio[0]["SUM(shares)"])):
            return apology("You dont that much!!!", 400)
        if (int(request.form.get("shares")) < 0):
            return apology("Cant sell less than nothing - a negative sell is a buy!!!", 400)

        # Get values
        shares = int(request.form.get("shares"))*(-1)
        symbol = request.form.get("symbol")
        dict = lookup(symbol)
        price = float(dict["price"])

        # Create time element
        now = datetime.now()

        # Add sell transaction to the ledger

        db.execute("INSERT INTO history (user_id, shares, symbol, price, time) VALUES(?,?,?,?,?)",session.get("user_id"), shares, symbol, price, now.strftime("%d/%m/%Y %H:%M:%S"))

        # Modify cash balance

        pre_trade_cash = db.execute("SELECT cash FROM users WHERE id IS ?", session.get("user_id"))
        pre_trade_cash = float(pre_trade_cash[0]["cash"])
        post_trade_cash = pre_trade_cash - (price * shares)
        db.execute("UPDATE users SET cash = ? WHERE id IS ?", post_trade_cash, session.get("user_id"))
        return redirect("/")

    else:
        # Extract Portfolio Data for Each user

        portfolio = db.execute("SELECT symbol,SUM(shares) FROM history WHERE user_id IS ? GROUP BY symbol", session.get("user_id"))

        return render_template("sell.html", portfolio=portfolio)


@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    if request.method == "POST":
        # VERIFY PASSWORD

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id IS ?", session.get("user_id"))

        # Ensure username exists and password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid password", 403)

        # TOP UP ACCOUNT
        amount = int(request.form.get("topup"))
        pre_trade_cash = db.execute("SELECT cash FROM users WHERE id IS ?", session.get("user_id"))
        pre_trade_cash = float(pre_trade_cash[0]["cash"])
        post_trade_cash = pre_trade_cash + amount
        db.execute("UPDATE users SET cash = ? WHERE id IS ?", post_trade_cash, session.get("user_id"))

        return redirect("/")
    else:
        return render_template("topup.html")

