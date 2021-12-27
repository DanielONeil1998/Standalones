import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/********************************************************** 
 *                   Instructions!
 * 
 *   Create a text file containing a series of integers each 
 *   on their own lines.
 * 
 *   Set the path to this text where instrcuted below; namely
 *   the first line of actual code within the main method.
 * 
 *   The program will then determine how many numbers are 
 *   larger than their predecessors.
 * 
 *   It's a simple program, but I figured I might as well
 *   freshen up on the basics over the winter break.
 * *********************************************************/

public class advent_01_2021 
{
    public static void main(String[] args) 
    {
       //Create file object
       //Set the file path here!
      File file = new File("input.txt");
      try 
      {
         //Create the scanner
         Scanner sc = new Scanner(file);

         //Creating the variables to track depth changes
         int previous=sc.nextInt(), current=0, increase=0;

         //Counting the increases
         while (sc.hasNextLine()) 
         {
            current=sc.nextInt();
            if (current > previous) increase++;
            previous=current;
         }

         //Printing out the data
         System.out.println("Total measurements larger than predecessor: "+ increase);
         sc.close();
     } 
     //Error management
     catch (FileNotFoundException e) 
     {
         e.printStackTrace();
     }
   }
 }