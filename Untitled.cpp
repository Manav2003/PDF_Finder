package com.urjanet.pdfFinder;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.CopyOption;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.nio.file.Files;
import org.apache.pdfbox.cos.COSDocument;
import org.apache.pdfbox.pdfparser.PDFParser;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.util.PDFTextStripper;

public class pdfFinder {
	
	public static void moveThePdf(File file , String myDirectoryPath) {

		  String filename = file.toString();
		  filename = filename.replace(myDirectoryPath,"");
		  filename = filename.replace("\\","");
		  //System.out.println(filename);
		  File theDir = new File(myDirectoryPath+"/SearchedFile/"+filename );
		  if (!theDir.exists()){
		      theDir.mkdirs();
		  }
		  Path sourcepath = file.toPath();
		  Path despath = theDir.toPath();

		  try {
			  CopyOption[] options = new CopyOption[]{
					  StandardCopyOption.REPLACE_EXISTING,
					  StandardCopyOption.COPY_ATTRIBUTES};
			  Files.copy(sourcepath, despath,options);
			} catch (IOException e) {
			    e.printStackTrace();
			}

	  
	}

	public static void main(String[] args) throws IOException {
		
		PDFParser parser = null;
	    
		//Creates an empty PDF document.
		PDDocument pdDoc = null;
	    
		//COSDoc is a temporary document file that will store the PDF. It will be automatically removed when the document is closed.
	    COSDocument cosDoc = null;
	    
	    //This method retrieves the text in a given document and returns it in the form of a String object.
	    PDFTextStripper pdfStripper;
	    
	    String parsedText;
	    String searchString = "Do not pay. Your account has a zero balance.";
		String myDirectoryPath = "/opt/UTC_LONG_JOB/SouthernCaliforniaEdisonTemplateProvider"; 
	    File dir = new File(myDirectoryPath);
	    File[] directoryListing = dir.listFiles();
	    if (directoryListing != null) {
	      for (File file : directoryListing) {
	    	  //System.out.println(file);
	  	      Boolean flag = false;

	    	  try {
	    		  try {
	    	        parser = new PDFParser(new FileInputStream(file));
	    	        parser.parse();
	    	        cosDoc = parser.getDocument();
	    	        pdfStripper = new PDFTextStripper();
	    	        pdDoc = new PDDocument(cosDoc);
	    	        parsedText = pdfStripper.getText(pdDoc);
	    	        System.out.println(parsedText);
	    	        if(parsedText.contains(searchString))
	    	        {
	    	        	flag = true;
	    	        }
	    		  }catch (Exception e) {
	    			  System.out.println("Hitting a Directory");
	    		  }
	    	        //System.out.println(parsedText);
	    	        
	    	    } catch (Exception e) {
	    	        e.printStackTrace();
	    	        try {
	    	            if (cosDoc != null)
	    	                cosDoc.close();
	    	            if (pdDoc != null)
	    	                pdDoc.close();
	    	        } catch (Exception e1) {
	    	            e1.printStackTrace();
	    	        }

	    	    }
	    	  if(flag == true)
	    	  {
	    		  moveThePdf(file,myDirectoryPath);
	    	      System.out.println("You got your File :)");
	    	      
	    	  }
	      }
	    } else {
	    	  System.out.println("No such directory EXISTS!");

	    }
	}

}