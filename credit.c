#include <math.h>
#include <cs50.h>
#include <stdio.h>

bool lenghtIsValid(int cardNumberLength);
int resultChecksum(long long int cardNumber, int cardNumberLength);
bool validateChecksum(int checksum);
string whatCreditCardIsIt(long long int cardNumber, int cardNumberLength);

int main(void)
{

    long long unsigned int cardNumber = 0;

    //we ask user card number
    while (cardNumber <= 0)
    {
        cardNumber = get_long("Number: ");
    }

    // we compute the length of card number
    int cardNumberLength = (int)(log10(cardNumber) + 1);

    // Possible numbers of digits : 13, 15, 16
    if (lenghtIsValid(cardNumberLength))
    {
        //we compute and test checksum
        int checksum = resultChecksum(cardNumber, cardNumberLength);

        bool checksumIsValid = validateChecksum(checksum);

        if (checksumIsValid)
        {
            string typeOfCreditCard = whatCreditCardIsIt(cardNumber, cardNumberLength);
            
            printf("%s\n", typeOfCreditCard);
        }
        else 
        {
            printf("INVALID\n");
        }
    }

    else 
    {
        printf("INVALID\n");
    }


}

bool lenghtIsValid(int cardNumberLength)
{
    if (cardNumberLength == 13 || cardNumberLength == 15 || cardNumberLength == 16)
    {
        return (true);
    }
    else {
        return (false);
    }
}

int resultChecksum(long long int cardNumber, int cardNumberLength)
{
    //test checksum
    int checksum = 0;

    // for every digit of card number
    for(int i = 1; i <= cardNumberLength; i++ )
    {
        //we get last digit
        int cardDigit = cardNumber % 10 ;

        // truncate the card number by one digit
        cardNumber = cardNumber / 10;

        //retrieve every two digits from the last one
        //add each digit to checksum
        if (i % 2 == 1)
        {
            checksum += cardDigit;
        }
        //retrieve every two digits from the second last one
        //multiply them by 2
        // if digit > 9, split into two digits (12 => 1 and 2)
        //add each result to checksum

        else if (i % 2 == 0)
        {
            cardDigit *= 2;

            if (cardDigit > 9) {
                    
                    int rightDigit = cardDigit % 10;
                    int leftDigit = cardDigit / 10;

                    checksum = checksum + rightDigit + leftDigit;
            }
            else {
                checksum += cardDigit;
            }
        }

    }
    return (checksum);
}

bool validateChecksum(int checksum)
{
    //if last digit of checksum is 0, 
    //checksum = valid
    if (checksum % 10 == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

string whatCreditCardIsIt(long long int cardNumber, int cardNumberLength)
{
    int secondToLastDigit = 0;
    int lastDigit = 0;
    
    for (int i = 1; i <= cardNumberLength; i++)
    {
        int cardDigit = cardNumber % 10;
        cardNumber = cardNumber / 10;
        
        if (i == cardNumberLength - 1)
        {
            secondToLastDigit = cardDigit;
        }
        if (i == cardNumberLength)
        {
            lastDigit = cardDigit;
        }
    }

    if (cardNumberLength == 13 && lastDigit == 4) 
    {
        return ("VISA");
    }
    if (cardNumberLength == 15 && lastDigit == 3)
    {
        if (secondToLastDigit == 4 || secondToLastDigit == 7)
        {
            return ("AMEX");
        }
    }
    if (cardNumberLength == 16)
    {
        if (lastDigit == 5)
        {
            if (1 <= secondToLastDigit && secondToLastDigit <= 5)
            {
                return ("MASTERCARD");
            }
        }
        if (lastDigit == 4)
        {
            return ("VISA");
        }
    }
    return ("INVALID");
}