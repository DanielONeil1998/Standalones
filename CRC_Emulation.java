import java.io.*;
import java.lang.String;
import java.util.Scanner;
import java.util.Random;

public class CRC_Emulation {
    public static void main(String[] args)
    {
        //Taking in the parameters from the user
        Scanner scan = new Scanner(System.in);
        System.out.println("Input message: ");
        String msg = scan.nextLine();
        System.out.println("Input reference polynomial: ");
        String refPol = scan.nextLine();

        //Enabling/disabling error generation functionality
        System.out.println("Introduce chance of random errors (y/n): ");
        String rnd = scan.nextLine();
        int random = 0;
        if(rnd.equals("y")) random = 1;
        Random rand = new Random();

        //Determining the transmitted string
        String transmit = msg+transmit(msg, refPol);

        //Printing out the messages
        System.out.printf("String to be transmitted: %s\n",transmit);
        //Performing error injection if feature enabled
        int randnum = 0;
        if (random==1)
        {
            for(int i = 0; i < transmit.length(); i++)
            {
                randnum = rand.nextInt(3);
                if (randnum==1)
                {
                    //Introducing bit switches in the message to simulate errors
                    if (transmit.charAt(i)=='1') transmit = transmit.substring(0,i)+"0"+transmit.substring(i+1,transmit.length());
                    else transmit = transmit.substring(0,i)+"1"+transmit.substring(i+1,transmit.length());
                }
            }
        }
        //Writing the results of the received message
        System.out.printf("String received: %s\n", transmit);
        System.out.printf("String reception status: %s\n", receive(transmit,refPol));
    }


    public static String transmit (String msg, String refPol)
    {
        //Ensuring there are no leading zeros
        while (refPol.charAt(0)!='1') refPol = refPol.substring(1,refPol.length());
        int refPolSize = refPol.length()-1;

        //Adding tailing zeros to work with CRC
        for (int i = 1; i <refPol.length(); i++) msg = msg.concat("0");

        //Performing the long division and outputting the answer
        return longDiv(msg, refPol, refPolSize).substring(longDiv(msg, refPol, refPolSize).length()-refPolSize,longDiv(msg, refPol, refPolSize).length());
    }


//Method to receive and decode the transmission
    public static String receive (String msg, String refPol)
    {
        while (refPol.charAt(0)!='1') refPol = refPol.substring(1,refPol.length());
        int refPolSize = refPol.length()-1;

        String decode = longDiv(msg, refPol, refPolSize);
        for ( int i = decode.length()-refPolSize; i < decode.length(); i++)
        {
            if(decode.charAt(i)=='1') return "Error Detected!\n";
        }
        return "No Error Detected\n";
    }

    public static String longDiv(String msg, String refPol, int refPolSize) {
        //Setting up parameters for the long division
        String output = "";
        String div;
        String remainder = msg.substring(0, refPolSize + 1);
        String holder = "";
        msg = msg.substring(refPolSize, msg.length());

        //Performing the long division

        while (true) {
            //Check if leading digit is a 1
            if (remainder.charAt(0) == '1') {
                div = refPol;
                output += '1';
            }
            //Check if leading digit is a zero
            else {
                div = "";
                output += '0';
                for (int i = 0; i < refPol.length(); i++) div = div.concat("0");
            }

            //Performs the long division
            for (int i = 1; i <= refPolSize; i++) {
                if (div.charAt(i) == remainder.charAt(i)) {
                    holder += "0";
                } else {
                    holder += "1";
                }
            }

            //Updates parameters post-division
            if ((msg.length() > 1)) remainder = holder + msg.charAt(1);
            holder = "";
            //Breaking out if the division is done
            if ((msg.length() <= 1)) {
                break;
            }
            msg = msg.substring(1, msg.length());
        }
        return msg+remainder;
    }
}