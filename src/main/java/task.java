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

public class task{
	
	public static void result(File file , String path) {

		  String target = file.toString();
		  target = target.replace(path,"");
		  target = target.replace("\\","");
		  //System.out.println(filename);
		  File theDir = new File(path+"/Target/"+target );
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
		
		PDFParser p = null;
	    //Creates an empty PDF document.
		
		PDDocument pD = null;
		//COSDoc is a temporary document file that will store the PDF. It will be automatically removed when the document is closed.
	    
		COSDocument cD = null;
	    //This method retrieves the text in a given document and returns it in the form of a String object.
	    
		PDFTextStripper pS;
	    String pT;
	    
	    String key = "10/28/2019";
		String path = "C:\\Users\\DELL\\OneDrive\\Documents\\Docs\\CommonDocs\\pdf"; 
	    File dir = new File(path);
	    File[] pdfList = dir.listFiles();
	    if (pdfList != null) {
	      for (File file : pdfList) {
	    	  //System.out.println(file);
	  	      Boolean flag = false;

	    	  try {
	    		  try {
	    	        p = new PDFParser(new FileInputStream(file));
	    	        p.parse();
	    	        cD = p.getDocument();
	    	        pS = new PDFTextStripper();
	    	        pD = new PDDocument(cD);
	    	        pT = pS.getText(pD);
//	    	        System.out.println(pT);
	    	        if(pT.contains(key))
	    	        {
	    	        	flag = true;
	    	        }
	    		  }catch (Exception e) {
	    			  System.out.println("Hitting a Directory");
	    		  }
	    	        //System.out.println(pT);
	    	        
	    	    } catch (Exception e) {
	    	        e.printStackTrace();
	    	        try {
	    	            if (cD != null)
	    	                cD.close();
	    	            if (pD != null)
	    	                pD.close();
	    	        } catch (Exception e1) {
	    	            e1.printStackTrace();
	    	        }

	    	    }
	    	  if(flag == true)
	    	  {
	    		  result(file,path);
	    	      System.out.println("You got your File :)");
	    	      
	    	  }
	      }
	    } else {
	    	  System.out.println("No such directory EXISTS!");

	    }
	}

}