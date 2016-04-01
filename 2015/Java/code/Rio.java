/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jcmd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 *
 * @author Fran
 */
public class Rio {
    List<String> list = new ArrayList<>();
    /**
     * Calls a program rio with his parameters.
     * @param u
     * @param l
     * @param c
     */
    public void start(double u, double l, double c, int n) {
        try {
            class Parse {
                int pos;
                Parse(){
                    pos = -1;
                }
                public boolean search (String line,String search) {
                    pos = line.indexOf(search);
                    return pos!=-1;
                }
                public String subString (String line,String search){
                    return line.substring(pos+search.length());
                }
            }
            Parse parse = new Parse();
            String line;
            InputStream stderr = null;
            InputStream stdout = null;
            
            // launch EXE and grab stdin/stdout and stderr
            Process process = new ProcessBuilder(
                    "C\\rio.exe",
                    "-u:"+u,"-l:"+l,"-c:"+c,"-n:"+n).start();
            stderr = process.getErrorStream();
            stdout = process.getInputStream();
            
            // parse the output
            BufferedReader br =
                    new BufferedReader (new InputStreamReader (stdout));
            boolean isVector=false;
            while ((line = br.readLine ()) != null) {
                if(parse.search(line,"pel="))
                    list.add(parse.subString(line, "pel="));
                if(parse.search(line, "A="))
                    list.add(parse.subString(line, "A="));
                if(parse.search(line, "B="))
                    list.add(parse.subString(line, "B="));
                if(parse.search(line, "C="))
                    list.add(parse.subString(line, "C="));
                if(isVector) {
                    list.add(line); //orden de aparicion: L,D,U,Z,Y,X
                    isVector = false;
                }
                if(parse.search(line,"Vector"))
                    isVector = true;
                
                if(parse.search(line,"SOLUTION::")) {
                    String text=splitEqually(parse.subString(line, "SOLUTION::"),120);
                    list.add(parse.subString(line,"SOLUTION::"));
                    JOptionPane.showMessageDialog(null,"The solution is:\n "+text,
                            "SOLUTION",JOptionPane.INFORMATION_MESSAGE);
                }
                System.out.println("[Stdout] " + line);
            }
            br.close();
            
            // clean up if any output in stderr
            br = new BufferedReader (new InputStreamReader (stderr));
            while ((line = br.readLine ()) != null) {
                System.out.println ("[Stderr] " + line);
                JOptionPane.showMessageDialog(null,"A error ocurred:\n "+line,
                            "ERROR",JOptionPane.ERROR_MESSAGE);
            }
            br.close();
        } catch (IOException ex) {
            Logger.getLogger(Rio.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    public static String splitEqually(String text, int size) {
        // Give the list the right capacity to start with. You could use an array
        // instead if you wanted.
        StringBuilder ret = new StringBuilder();

        for (int start = 0; start < text.length(); start += size) {
            ret.append(text.substring(start, Math.min(text.length(), start + size)));
            ret.append('\n');
        }
        return ret.toString();
    }   

    public List<String> getList() {
        return list;
    }
    
    
}
