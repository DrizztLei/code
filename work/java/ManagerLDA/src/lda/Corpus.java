/*
 * <summary></summary>
 * <author>He Han</author>
 * <email>hankcs.cn@gmail.com</email>
 * <create-date>2015/1/29 17:03</create-date>
 *
 * <copyright file="Corpus.java" company="上海林原信息科技有限公司">
 * Copyright (c) 2003-2014, 上海林原信息科技有限公司. All Right Reserved, http://www.linrunsoft.com/
 * This source is subject to the LinrunSpace License. Please contact 上海林原信息科技有限公司 to get more information.
 * </copyright>
 */
package lda;

import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import lda.Vocabulary;

public class Corpus
{
	List<int[]> documentList;
	public static List<String[]> topicWord;
	public static List<String> documentName;
	public static int count = 0;
	public static int TYPE, NUMBER, SUM, RANK;

	Vocabulary vocabulary;

	public Corpus()
	{
		documentList = new LinkedList<int[]>();
		documentName = new LinkedList<String>();
		vocabulary = new Vocabulary();
		topicWord = new LinkedList<>();
	}

	public int[] addDocument(List<String> document)
	{
		int size = document.size();
		int[] doc = new int[size];
		String[] info = new String[size];
		int i = 0;
		for (String word : document)
		{
			int id = vocabulary.getId(word, true);
			info[i] = word;
			doc[i] = id;
			i++;
		}
		info = countWord(info);

		topicWord.add(count, info);
		documentList.add(doc);
		count++;
		return doc;
	}

	public static boolean containStr(String[] array, String aim)
	{
		int hash = aim.hashCode();
		for (int i = 0; i < array.length; i++)
		{
			if (array[i] != null && array[i].hashCode() == hash)
			{
				return true;
			}
		}
		return false;
	}

	public static String[] countWord(String[] words)
	{
		Map<String, Integer> record = new HashMap<>();
		for (int i = 0; i < words.length; i++)
		{
			String word = words[i];
			if (record.containsKey(word))
			{
				Integer value = record.get(word);
				record.put(word, value + 1);
			}
			else
			{
				record.put(word, new Integer(1));
			}
		}

		String[] result = new String[RANK];

		int minValue = -1, minCount = 0, position = 0;

		for (int i = 0; i < words.length; i++)
		{
			String word = words[i];
			Integer value = record.get(word);

			if (containStr(result, word))
			{
				continue;
			}

			if (position < RANK)
			{
				if (minValue == -1)
				{
					result[position] = word;
					minCount = 0;
					minValue = value.intValue();
				}
				else if (value.intValue() > minValue)
				{
					result[position] = word;
				}
				else
				{
					minValue = value.intValue();
					minCount = position;
					result[position] = word;
				}
				position++;
			}
			else if (value.intValue() > minValue)
			{
				result[minCount] = word;
				Integer min = record.get(result[0]);
				minCount = 0;

				for (int j = 1; j < RANK; j++)
				{
					Integer compare = record.get(result[j]);

					if (min.intValue() > compare.intValue())
					{
						min = compare;
						minCount = j;
					}
				}
			}
		}
		return result;
	}

	public int[][] toArray()
	{
		return documentList.toArray(new int[0][]);
	}

	public int getVocabularySize()
	{
		return vocabulary.size();
	}

	@Override
	public String toString()
	{
		final StringBuilder sb = new StringBuilder();
		for (int[] doc : documentList)
		{
			sb.append(Arrays.toString(doc)).append("\n");
		}
		sb.append(vocabulary);
		return sb.toString();
	}

	/**
	 * Load documents from disk
	 *
	 * @param folderPath
	 *            is a folder, which contains text documents.
	 * @return a corpus
	 * @throws IOException
	 */
	public static Corpus load(String folderPath) throws IOException
	{
		Corpus corpus = new Corpus();
		File folder = new File(folderPath);
		for (File file : folder.listFiles())
		{
			String fileName = file.getName();
			// System.out.println(fileName);
			Corpus.documentName.add(fileName);
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			String line;
			List<String> wordList = new LinkedList<String>();
			while ((line = br.readLine()) != null)
			{
				String[] words = line.split(" |\t|\n|	　|	");
				for (String word : words)
				{
					char temp = '　';					
					word = word.replace(temp, ' ');
					word = word.replaceAll("\\s*", "");
					if (word.length() < 2)
					{
						continue;
					}
					wordList.add(word);
				}
			}
			br.close();
			corpus.addDocument(wordList);
		}
		if (corpus.getVocabularySize() == 0)
			return null;

		return corpus;
	}

	public Vocabulary getVocabulary()
	{
		return vocabulary;
	}

	public int[][] getDocument()
	{
		return toArray();
	}

	public static int[] loadDocument(String path, Vocabulary vocabulary) throws IOException
	{
		BufferedReader br = new BufferedReader(new FileReader(path));
		String line;
		List<Integer> wordList = new LinkedList<Integer>();
		while ((line = br.readLine()) != null)
		{
			String[] words = line.split(" ");
			for (String word : words)
			{
				if (word.trim().length() < 2)
					continue;
				Integer id = vocabulary.getId(word);
				if (id != null)
					wordList.add(id);
			}
		}
		br.close();
		int[] result = new int[wordList.size()];
		int i = 0;
		for (Integer integer : wordList)
		{
			result[i++] = integer;
		}
		return result;
	}
}
