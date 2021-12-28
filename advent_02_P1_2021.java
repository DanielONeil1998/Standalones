import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/********************************************************** 
 *                   Instructions!
 * 
 *   Create a text file of the following format;
 * 
 *   direction x
 * 
 *   Replace 'direction' with any of the following; forward,
 *   up, or down. Replace 'x' with any integer.
 * 
 *   Set the path to this text where instructed below; namely
 *   the first line of actual code within the main method.
 * 
 *   The program will then output the total horizontal 
 *   distance travelled, depth achieved, and the product
 *   of those two numbers.
 * 
 *   See the following link for complete code requirments
 *   https://adventofcode.com/2021/day/2
 * 
 * *********************************************************/

public class advent_02_P1_2021 {
    public static void main(String[] args) 
    {
        //Create file object
        //Set the file path here!
        File file = new File("src\\input02.txt");
        try 
        {
            //Create the scanner
            Scanner sc = new Scanner(file);

            //Creating the variables to track position changes
            int horizontal=0, depth=0;
            String breakdown[], input;

            //Reading in the coordinate changes
            while (sc.hasNextLine()) 
            {
                input=sc.nextLine();
                breakdown = input.split(" ", 2);
                if(breakdown[0].equals("down")) depth += Integer.parseInt(breakdown[1]);
                else if(breakdown[0].equals("up")) depth -= Integer.parseInt(breakdown[1]);
                else horizontal += Integer.parseInt(breakdown[1]);
            }

            //Printing out the data
            System.out.println("Forward: "+ horizontal);
            System.out.println("Depth: "+depth);
            System.out.println("Multiplied: "+(depth*horizontal));
            sc.close();
        } 
     //Error management
     catch (FileNotFoundException e) 
     {
         e.printStackTrace();
     }
    }
}
