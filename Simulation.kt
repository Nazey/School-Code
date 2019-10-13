/*
 * Author: Brian Massino, bmassino2017@my.fit.edu
 * Author: Matt Intriago, mintriago2017@my.fit.edu
 * Course: CSE 4250, Spring 2019
 * Project: Proj2, Simulation (TM)
 * Implementation:  Kotlin version  1.3.50 (JRE 1.8.0_221-b11)
 * Description: program to simulate step by step the execution of a Turning machine (TM for short) on given input strings.
 * The description of the TM will be in a US-ASCII text file. The name of the file will be a command line argument to the        
 * program. Zero or more strings on which to perform the simulation will be given in the standard input stream.
 * compile like this: kotlinc -d tm.jar -include-runtime TM.kt
 */
import java.io.File
import java.lang.Boolean.FALSE
import java.lang.Boolean.TRUE
import java.util.Scanner

fun main(args: Array<String>){
    var inputFile = File(args[0]).bufferedReader()
    var firstLine = inputFile.readLine().split("\\s+".toRegex())            // grabs first line, delimit it so that all extra spaces are removed
    val numInstructions = (firstLine[0].toInt())                            // how many lines to read
    var alphabet = firstLine[1].toString()                                  // n letter alphabet
    var blankCharacter = firstLine[1][firstLine[1].length-1]                // stores last blank character
    var action = CharArray(numInstructions)                                 // R, L, Y, or N
    var nextState = Array(numInstructions, {IntArray(alphabet.length)})     // creating array of ints to point to next statement
    var replaceWith = Array(numInstructions, {CharArray(alphabet.length)})  // creating array of chars for which to replace with
    var comment = Array(numInstructions, {String()})

    val scanman  = Scanner(System.`in`)                                                     // Init Scanner
    var userLine = mutableListOf<String>()                                                  // create list for user input
    while(scanman.hasNextLine()){                                                           // while input is still being entered
        var input_str = scanman.nextLine().replace("\\s".toRegex(), "")         // take the input in
        if(input_str.isBlank())                                                             // if it's blank, stop reading input
            break
        userLine.add(input_str)
    }


   for (i in 0 until numInstructions){                                       //for each line, store all of the instructions for the turing machine

        var str = inputFile.readLine()                                       //get the line
        var eachLine = str.split("\\s+".toRegex())                           //splits into a list of strings, to do away with varying spacing
        action[i] = eachLine[1].single()

        var placeHolder = 2
        for(k in alphabet.indices){
            nextState[i][k] = eachLine[placeHolder].trim().toInt()          //filling out arrays for turing machine, this one holding the next state of the TM
            placeHolder++
        }

        for(j in alphabet.indices){
            replaceWith[i][j] = eachLine[placeHolder].trim().single()       //holds what to replace each letter in the alphabet with
            placeHolder++
        }

        var fullComment = ""                                                //grabbing all of the strings in eachLine for the comment,
        for (k in placeHolder..eachLine.size-1){                            //concatenating them with a space and then adding to the list of comments
            if(k == eachLine.size-1){
                fullComment += eachLine[k]
            } else fullComment += eachLine[k] + " "

        }
        comment[i] = fullComment
    }

    if(userLine.isNotEmpty()) {                          //check to see if there is any input
        for(i in userLine.indices){                      //main function to do turing machine results
            var input =  mutableListOf<Char>()
            input.add(0,blankCharacter)             //add blank character to beginning

            var temp = 0
            for(k in 1 until userLine[i].length+1){
                input.add(k, userLine[i][temp])
                temp++
                if(k == userLine[i].length){
                    input.add(input.size,blankCharacter) //add blank character to end
                }
            }

            var end = 0
            var lineCount = 0
            var state = 0
            var index = 1

           while(end != 1){
                printStateString(lineCount, state, index, comment, input)

                for(k in alphabet.indices){                                 //for every letter in the alphabet
                    if(input[index] == alphabet[k]){                        //if we find a match, first check to see if it needs a blank character at the beginning or end,
                        if(index == 0 && input[index] != blankCharacter){   //then replace the character with corresponding character in the TM, and update the corresponding state
                            input.add(0, blankCharacter)
                            index++
                        } else if(index == input.size  && input[index] != blankCharacter){
                            input.add(input.size, blankCharacter)

                        }
                        input[index] = replaceWith[state][k]
                        state = nextState[state][k]

                        break
                    }
                }
                if(action[state] == 'R'){                                   //if right, move right, else move left
                    index++
                } else if(action[state] == 'L'){
                    index--
                } else if(action[state] == 'Y' || action[state] == 'N'){    //else the simulation is done
                    end = 1
                    lineCount++
                    printStateString(lineCount, state, index, comment, input)
                    break
                }

                lineCount++                                                  //increment the line count, for output purposes
            }

            if(i != userLine.size-1)
                println()
        }
    }



}

fun printStateString(lineCount: Int, state: Int, index: Int, comment: Array<String>, input: MutableList<Char>){     //function to print out current line with input string, with required output/formatting
    print("$lineCount: state=$state  ")
    for(k in 0 until input.size){
        if(k == index)
            print("["+input[k]+"] ")
        else print(input[k] + " ")

    }
    println("   " + comment[state])
}

