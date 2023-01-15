-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Gets the crime scene reports on the day - three witnesses all mention the bakery
SELECT * FROM crime_scene_reports WHERE (year = 2021 AND month = 7 AND day = 28);

SELECT * FROM interviews WHERE (year = 2021 AND month = 7 AND day > 25 AND day < 31 );

SELECT DISTINCT account_number FROM atm_transactions WHERE (year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street");

SELECT * FROM phone_calls WHERE (year = 2021 AND month = 7 AND day = 28 AND duration < 60);

SELECT * FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE (year = 2021 AND month = 7 AND day = 28 AND duration < 60))
AND license_plate IN
(SELECT license_plate from bakery_security_logs WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10));

SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE (year = 2021 AND month = 7 AND day = 28 AND duration < 60));

SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE (year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = 8)) AND passport_number IN
(SELECT passport_number FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE (year = 2021 AND month = 7 AND day = 28 AND duration < 60))
AND license_plate IN
(SELECT license_plate from bakery_security_logs WHERE (year = 2021 AND month = 7 AND day = 28)));

-----------------------------
-- Starting from Scratch
SELECT * FROM people WHERE
license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE (year = 2021 AND month = 7 AND day = 28 AND HOUR = 10 AND MINUTE < 26 AND activity = "exit")) AND
passport_number IN (SELECT passport_number FROM passengers where flight_id = 36) AND
phone_number IN (SELECT caller FROM phone_calls WHERE (year = 2021 AND month = 7 AND day = 28 AND duration <60)) AND
id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND (year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw")));

