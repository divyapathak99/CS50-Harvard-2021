-- Keep a log of any SQL queries you execute as you solve the mystery.
-- first let's check what happened on july 28, 2020 on Chamberlin Street. for which check the description of the crime in the crime_scene_reports table on that day.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street ='Chamberlin Street';
-- since everyone is mentioning courthouse then let's check what is in there.
-- .schema courthhouse_security_logs

SELECT transcript FROM interviews WHERE day=28 AND month=7 AND year=2020;

--Thief
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year=2020 AND day=28 AND month=7 AND hour=10 AND minute>15 AND minute<=25 AND activity='exit')
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year=2020 AND day=28 AND month=7 AND atm_location='Fifer Street' AND transaction_type='withdraw'))
AND phone_number IN (SELECT caller FROM phone_calls WHERE year=2020 AND day=28 AND month=7 AND duration<60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id= (SELECT id FROM flights WHERE year=2020 AND day=29 AND month=7 AND origin_airport_id=8 ORDER BY hour,minute LIMIT 1));






--DESTINATION ID: city
SELECT city FROM airports WHERE id =( SELECT destination_airport_id FROM flights WHERE year=2020 AND day=29 AND month=7 AND origin_airport_id=8 AND hour=8 AND minute=20);

--ACCOMPLICE
SELECT name FROM people WHERE phone_number =(SELECT receiver FROM phone_calls WHERE caller= (SELECT phone_number FROM people WHERE name='Ernest') AND year=2020 AND day=28 AND month=7 AND duration<60);





SELECT  name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year=2020 AND day=28 AND month=7 AND hour=10 AND minute>15 AND minute<=25 AND activity='exit')
AND
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year=2020 AND day=28 AND month=7 AND atm_location='Fifer Street' AND transaction_type='withdraw'))
AND
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id= (SELECT id FROM flights WHERE year=2020 AND day=29 AND month=7 AND origin_airport_id=8 ORDER BY hour,minute LIMIT 1))