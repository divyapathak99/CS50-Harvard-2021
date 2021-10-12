SELECT  name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year=2020 AND day=28 AND month=7 AND hour=10 AND minute>15 AND minute<=25 AND activity='exit')
AND
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year=2020 AND day=28 AND month=7 AND atm_location='Fifer Street' AND transaction_type='withdraw'))
AND
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id= (SELECT id FROM flights WHERE year=2020 AND day=29 AND month=7 AND origin_airport_id=8 ORDER BY hour,minute LIMIT 1))