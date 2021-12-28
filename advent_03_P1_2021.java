import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Arrays;

/********************************************************** 
 *                   Instructions!
 * 
 *   Create a text file of the following format; each lines
 *   strictly 1's and 0's with no additional characters.
 *   Each line contains the same amount of 1's and 0's.
 * 
 *   This program will determine the most frequent character
 *   per column, whether it is a 1 or a 0, and generate a 
 *   binary number based off of which columns had which more 
 *   frequent character. It will also find the binary number 
 *   for the lower of the two.
 * 
 *   For example, the following data;
 * 
 *   001
 *   100
 *   110
 * 
 *   would generate the two numbers 100 and 011. These binary
 *   numbers are then converted into decimal notation. These
 *   decimal notations are then output alongside the product
 *   of the two numbers.
 * 
 *   See the following link for complete code requirments
 *   https://adventofcode.com/2021/day/3
 * 
 * *********************************************************/

public class advent_03_P1_2021 {
    public static void main(String[] args) 
    {
        //Create file object
        //Set the file path here!
        File file = new File("src\\input03.txt");
        try 
        {
            //Create the scanner
            Scanner sc = new Scanner(file);

            //Creating the variables to track individiual data columns
            String input;
            input = sc.nextLine();
            int [] num = new int[input.length()+1];
            int [] answer = new int[input.length()];

            //Calling the array to determine amount of 1's per data column
            num = arrayPopulate(input, num,file, sc);

            //Calculating which columns had more 1's than 0's
            for (int i = 0; i <num.length-1; i++) 
            {
                if (num[i]>(num[num.length-1]/2)) answer[i]=1;
                else answer[i]=0;
            }

            //Converting from binary to decimal
            int max = maxPower(answer);
            int min = minPower(answer);

            //Outputting necessary information
            System.out.println("Frequent: "+max);
            System.out.println("Infrequent: "+min);
            System.out.println("Total: "+(max*min));

            sc.close();
        } 

        //Error management
        catch (FileNotFoundException e) 
        {
            e.printStackTrace();
        }
    }

        //Method to populate the arrays determining amount of 1's and 0's per data column
        public static int[] arrayPopulate(String input, int [] num, File file, Scanner sc)
        {
            while (sc.hasNextLine()) 
            {
                num[num.length-1] += 1;
                for (int i =0; i<num.length-1; i++) if (input.charAt(i)=='1') num[i] +=1;
                input = sc.nextLine();
            }
            num[num.length-1] += 1;
            for (int i =0; i<(num.length-1); i++) if (input.charAt(i)=='1') num[i] +=1;
            return num;
        }

        //Method to determine binary num created by columns with majority 1
        public static int maxPower(int [] num)
        {
            String[] holder = new String[num.length];
            for (int i =0; i<(num.length); i++) holder[i] = String.valueOf(num[i]);
            return Integer.parseInt(Arrays.toString(holder).replaceAll("\\[|\\]|,|\\s", ""),2); 
        }

        //Method to determine binary num created by columns with majority 1
        public static int minPower(int [] num)
        {
            String[] holder = new String[num.length];
            for (int i =0; i<(num.length); i++)
            {
                if (String.valueOf(num[i]).equals("1")) holder[i] = "0";
                else holder[i] = "1";
            }
            return Integer.parseInt(Arrays.toString(holder).replaceAll("\\[|\\]|,|\\s", ""),2); 
        }

}
