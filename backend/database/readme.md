# Tietokanta

Tietokanta sisältää kaksi proseduuria:
- customerData(int customerid):
    - voidaan hakea tilit joihin käyttäjällä on käyttöoikeus.
- accountData(char accountid):
    - voidaan hakea käyttäjät joilla on käyttöoikeus tiliin.
- withdraw(int amount, char id), deposit(int amount, char id):
    - Voidaan tehdä talletuksia ja nostoja, proseduuri hoitaa tarvittavat tarkistukset ja tietokannan saldon päivittämisen

![alt text](bank_er.png)