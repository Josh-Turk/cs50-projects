#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    bool validNum = false;
    string cardType = "INVALID\n";

    // get cc number from user
    long number = get_long("Enter CC Number: ");
    // int test = 4003600000000014 % 100 / 10;

    // convert number to char to get # of digits
    char holder[20] = {};
    sprintf(holder, "%ld", number); // number gets put into holder (data type long)
    int length = (int) strlen(holder);

    // deconstruct cc number into array and sum
    int mult[20] = {}; // array to hold numbers to be multiplied
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        if ((i + 1) % 2 == 0)
        {
            mult[i / 2] = number % (long) pow(10, i + 1) / (long) pow(10, i); // since
        }
        else
        {
            sum += number % (long) pow(10, i + 1) / (long) pow(10, i);
        }
    }

    // calculate mult array length
    int arrLength = 0;
    if (length % 2 == 0)
    {

        arrLength = length / 2;
    }
    else
    {

        arrLength = (length - 1) / 2;
    }

    // multiply by 2 and sum mult array (every other cc number)
    int multSum = 0;
    for (int i = 0; i <= arrLength; i++)
    {
        if (mult[i] * 2 > 9) // deconstruct double digit products
        {
            multSum += ((mult[i] * 2) % 10) + ((mult[i] * 2) / 10);
        }
        else
        { // handling for single digit
            multSum += mult[i] * 2;
        }
    }

    int totSum = sum + multSum;
    // printf("totSum: %d\n", totSum);

    // check if cc number passes the checksum
    if (totSum % 10 == 0)
    {
        validNum = true;
    }

    // once valid, check which type of card based on length and starting numbers
    if (validNum)
    {
        if (length == 15)
        {
            if (number / 10000000000000 == 37 || number / 10000000000000 == 34)
            {
                cardType = "AMEX\n";
            }
        }
        else if (length == 16)
        {
            if (number / 100000000000000 >= 51 && number / 100000000000000 <= 55)
            {
                cardType = "MASTERCARD\n";
            }
            else if (number / 1000000000000000 == 4)
            {
                cardType = "VISA\n";
            }
        }
        else if (length == 13)
        {
            if (number / 1000000000000000 == 4)
            {
                cardType = "VISA\n";
            }
        }
    }

    printf("%s", cardType);
}
