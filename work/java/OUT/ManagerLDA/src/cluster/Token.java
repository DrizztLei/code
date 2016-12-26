package cluster;

import java.io.FileReader;
import java.io.IOException;
import java.util.List;

import edu.stanford.nlp.ling.CoreLabel;
import edu.stanford.nlp.ling.HasWord;
import edu.stanford.nlp.process.CoreLabelTokenFactory;
import edu.stanford.nlp.process.DocumentPreprocessor;
import edu.stanford.nlp.process.PTBTokenizer;

public class Token
{

	public static void main(String[] args) throws IOException
	{
		args = new String[1];
		
		args[0] = "/home/elvis/work/java/ManagerLDA/experiment/experiment.txt";
		
		for (String arg : args)
		{
			// option #1: By sentence.
			DocumentPreprocessor dp = new DocumentPreprocessor(arg);
			
			for (List<HasWord> sentence : dp)
			{
				System.out.println("SENTENCE : " + sentence);
			}
			
			// option #2: By token
			PTBTokenizer<CoreLabel> ptbt = new PTBTokenizer<>(new FileReader(arg), new CoreLabelTokenFactory(), "");
			
			while (ptbt.hasNext())
			{
				CoreLabel label = ptbt.next();
				System.out.println("Lable for : " + label);
			}
		}
	}
}