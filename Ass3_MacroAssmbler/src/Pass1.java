import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedHashMap;

public class Pass1 {

	public static void main(String[] args) throws IOException{
		BufferedReader br=new BufferedReader(new FileReader("input.asm"));
		
		FileWriter mnt=new FileWriter("mnt.txt");
		FileWriter mdt=new FileWriter("mdt.txt");
		FileWriter kpdt=new FileWriter("kpdt.txt");
		FileWriter pnt=new FileWriter("ALA.txt");
		FileWriter ir=new FileWriter("intermediate.txt");
		LinkedHashMap<String, Integer> pntab=new LinkedHashMap<>();  // pntab == ALA
		String line;
		String Macroname = null;
		int mdtp=1,
			kpdtp=0,
			paramNo=1,
			pp=0,		//positional parameter count
			kp=0,		//keyword parameter count
			flag=0;
		while((line=br.readLine())!=null)
		{
			
			String parts[]=line.split("\\s+");
			if(parts[0].equalsIgnoreCase("MACRO") && parts.length == 1)
			{
				flag=1;		//macro definition found
				line=br.readLine(); // next line
				parts=line.split("\\s+");
//				boolean labl = false;
				if(parts[0].contains("&")) {
					parts[0] = parts[0].replaceAll("[&,]", "");
					pntab.put(parts[0], paramNo++);
//					System.out.println(parts[0] + paramNo);
					System.out.println("\n"+parts[0] +" "+ pntab.get(parts[0]));
					pp++;
//					labl = true;
				}
				Macroname = parts[1];
				if(parts.length<=2)
				{
					mnt.write(Macroname +"\t"+pp+"\t"+kp+"\t"+mdtp+"\t"+(kp==0?kpdtp:(kpdtp+1))+"\n");
					continue;
				}
				for(int i=2;i<parts.length;i++) //processing of parameters
				{
					parts[i]=parts[i].replaceAll("[&,]", "");
					//System.out.println(parts[i]);
					if(parts[i].contains("="))
					{
						++kp;
						String keywordParam[]=parts[i].split("=");
						pntab.put(keywordParam[0], paramNo++);
						if(keywordParam.length==2)
						{
							kpdt.write(keywordParam[0]+"\t"+keywordParam[1]+"\n");
						}
						else
						{
							kpdt.write(keywordParam[0]+"\t-\n");
						}
					}
					else
					{
						pntab.put(parts[i], paramNo++);
						pp++;
					}
				}
				mnt.write(parts[1]+"\t"+pp+"\t"+kp+"\t"+mdtp+"\t"+(kp==0?kpdtp:(kpdtp+1))+"\n");
				kpdtp=kpdtp+kp;
				//System.out.println("KP="+kp);
				
				
			}
			else if(parts[0].equalsIgnoreCase("MEND"))
			{
				mdt.write(line+"\n");
				flag=kp=pp=0;
				mdtp++;
				paramNo=1;
				pnt.write(Macroname+":\t");
				Iterator<String> itr=pntab.keySet().iterator();
				while(itr.hasNext())
				{
					pnt.write(itr.next()+"\t");
				}
				pnt.write("\n");
				pntab.clear();
			}
			else if(flag==1)
			{
				for(int i=0;i<parts.length;i++)
				{
					if(parts[i].contains("&"))
					{
						parts[i]=parts[i].replaceAll("[&,]", "");
						mdt.write("(P,"+pntab.get(parts[i])+")\t");
						System.out.println("\n"+parts[i] + pntab.get(parts[i]));
					}
					else
					{
						mdt.write(parts[i]+"\t");
					}
				}
				mdt.write("\n");
				mdtp++;
			}
			else
			{
				ir.write(line+"\n");
			}
		}
		br.close();
		mdt.close();
		mnt.close();
		ir.close();
		pnt.close();
		kpdt.close();
		System.out.println("MAcro PAss1 Processing done. :)");
	}

}