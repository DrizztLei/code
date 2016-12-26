package lda;

import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Map;
import java.util.Scanner;

public class Main
{
	public static final int TYPE = 15;
	public static final int NUMBER = 10;
	public static final int SUM = 2;
	public static final int RANK = 6;

	public static String[][][] info = new String[TYPE][NUMBER][SUM];

	public static ArrayList<String[][]> array = new ArrayList<>();
	public static Scanner scanner = new Scanner(System.in);

	public static void main(String[] args) throws IOException
	{
		Corpus.TYPE = TYPE;
		Corpus.NUMBER = NUMBER;
		Corpus.SUM = SUM;
		Corpus.RANK = RANK;

		Corpus corpus = Corpus.load("/home/elvis/work/java/ManagerLDA/data/mini");

		LdaGibbsSampler ldaGibbsSampler = new LdaGibbsSampler(corpus.getDocument(), corpus.getVocabularySize());

		ldaGibbsSampler.gibbs(TYPE);

		double[][] phi = ldaGibbsSampler.getPhi();

		Map<String, Double>[] topicMap = LdaUtil.translate(phi, corpus.getVocabulary(), NUMBER);

		Main.show(topicMap);

		/*
		 * for (int i = 0; i < TYPE; i++) { System.out.println("STEP " + i); for
		 * (int j = 0; j < NUMBER; j++) { for (int k = 0; k < SUM; k++) {
		 * System.out.println(info[i][j][k]); } } }
		 */
		/*
		 * String topic = info[3][3][0]; System.out.println("TOPIC : " + topic);
		 * System.out.println("TOPIC FIND FILE"); LinkedList<String> rearchFile
		 * = topicFindFile(topic); for (int i = 0; i < rearchFile.size(); i++) {
		 * System.out.print(rearchFile.get(i) + "\t"); } System.out.println();
		 * 
		 * System.out.println("TOPIC FIND TOPIC"); LinkedList<String>
		 * rearchTopic = topicFindTopic(info[3][3][0]); for (int i = 0; i <
		 * rearchTopic.size(); i++) { System.out.print(rearchTopic.get(i) +
		 * "\t"); } System.out.println(); System.out.println("FILE FIND FILE");
		 * LinkedList<String> fileReasearch =
		 * fileFindFIle(corpus.documentName.get(3)); for (int i = 0; i <
		 * fileReasearch.size(); i++) { System.out.print(fileReasearch.get(i) +
		 * "\t"); } System.out.println();
		 */
	}

	public static LinkedList<String> fileFindFIle(String file)
	{
		LinkedList<String> result = new LinkedList<>();
		LinkedList<String> search = fileFindTopic(file);
		for (int i = 0; i < search.size(); i++)
		{
			String topic = search.get(i);
			LinkedList<String> fileSet = topicFindFile(topic);
			for (int j = 0; j < fileSet.size(); j++)
			{
				String fileName = fileSet.get(j);
				result.add(fileName);
			}
		}
		return result;
	}

	public static LinkedList<String> topicFindTopic(String topic)
	{
		LinkedList<String> result = new LinkedList<>();
		int hash = topic.hashCode();
		for (int i = 0; i < TYPE; i++)
		{
			for (int j = 0; j < NUMBER; j++)
			{
				String word = info[i][j][0];
				if (word == null)
				{
					continue;
				}
				if (hash == info[i][j][0].hashCode())
				{
					for (int k = 0; k < NUMBER; k++)
					{
						result.add(info[i][k][0]);
					}
					return result;
				}
			}
		}
		return result;
	}

	public static LinkedList<String> topicFindFile(String topic)
	{
		LinkedList<String> result = new LinkedList<>();
		int topicHash = topic.hashCode();
		for (int i = 0; i < Corpus.documentName.size(); i++)
		{
			for (int j = 0; j < Corpus.topicWord.get(i).length; j++)
			{
				String word = Corpus.topicWord.get(i)[j];
				if (word == null)
				{
					continue;
				}
				if (word.hashCode() == topicHash)
				{
					String fileName = Corpus.documentName.get(i);
					result.add(fileName);
				}
			}
		}
		return result;
	}

	public static LinkedList<String> fileFindTopic(String topic)
	{
		LinkedList<String> result = new LinkedList<>();
		int hash = topic.hashCode();
		for (int i = 0; i < Corpus.documentName.size(); i++)
		{
			String fileName = Corpus.documentName.get(i);
			if (fileName == null)
			{
				continue;
			}
			if (fileName.hashCode() == hash)
			{
				for (int j = 0; j < Corpus.topicWord.get(i).length; j++)
				{
					String findTopic = Corpus.topicWord.get(i)[j];
					result.add(findTopic);
				}
				return result;
			}
		}
		return result;
	}

	public static void show(Map<String, Double>[] map)
	{
		int i = 0;
		for (Map<String, Double> topicMap : map)
		{
			int j = 0;
			for (Map.Entry<String, Double> entry : topicMap.entrySet())
			{
				info[i][j][0] = entry.getKey();
				info[i][j][1] = entry.getValue() + "";
				j++;
			}
			i++;
		}
	}
}
