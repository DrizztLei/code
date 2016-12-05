package cluster;

import java.util.ArrayList;
import java.util.Set;

public class LdaGibbsSampling
{
	public static class modelparameters
	{
		float alpha = 0.5f; // usual value is 50 / K
		float beta = 0.1f;// usual value is 0.1
		int topicNum = 100;
		int iteration = 100;
		int saveStep = 10;
		int beginSaveIters = 50;
	}

	/**
	 * Get parameters from configuring file. If the configuring file has value
	 * in it, use the value. Else the default value in program will be used
	 * 
	 * @param ldaparameters
	 * @param parameterFile
	 * @return void
	 */
	private static void getParametersFromFile(modelparameters ldaparameters, String parameterFile)
	{
		// TODO Auto-generated method stub
		ArrayList<String> paramLines = new ArrayList<String>();
		paramLines = FileUtil.readList(parameterFile);
		for (String line : paramLines)
		{
			String[] lineParts = line.split("\t");
			switch (parameters.valueOf(lineParts[0]))
			{
			case alpha:
				ldaparameters.alpha = Float.valueOf(lineParts[1]);
				break;
			case beta:
				ldaparameters.beta = Float.valueOf(lineParts[1]);
				break;
			case topicNum:
				ldaparameters.topicNum = Integer.valueOf(lineParts[1]);
				break;
			case iteration:
				ldaparameters.iteration = Integer.valueOf(lineParts[1]);
				break;
			case saveStep:
				ldaparameters.saveStep = Integer.valueOf(lineParts[1]);
				break;
			case beginSaveIters:
				ldaparameters.beginSaveIters = Integer.valueOf(lineParts[1]);
				break;
			}
		}
	}

	public enum parameters
	{
		alpha, beta, topicNum, iteration, saveStep, beginSaveIters;
	}

	/**
	 * 训练LDA主题模型，对给定的测试样本集进行主题预测，找出每个样本的最大概率主题下的前20个词的集合，作为该测试样本集的主题代表关键词集合
	 * 
	 * @param trainPathDir
	 * @param parameterFile
	 * @param resultPath
	 * @param testPath
	 * @return
	 * @throws IOException
	 */
	
	public Set<Word> trainAndPredictLDA(String trainPathDir, String parameterFile, String resultPath, String testPath)
			throws IOException
	{
		modelparameters ldaparameters = new modelparameters();
		getParametersFromFile(ldaparameters, parameterFile);
		Documents docSet = new Documents();
		docSet.readDocs(trainPathDir);
		System.out.println("wordMap size " + docSet.termToIndexMap.size());
		FileUtil.mkdir(resultPath);
		LdaModel model = new LdaModel(ldaparameters);
		System.out.println("1 Initialize the model ...");
		model.initializeModel(docSet);
		System.out.println("2 Learning and Saving the model ...");
		model.inferenceModel(docSet);
		System.out.println("3 Output the final model ...");
		// model.saveIteratedModel(ldaparameters.iteration, docSet);
		// System.out.println("Done!");

		// 预测新文本
		Documents testDocs = new Documents();
		List<Message> messages = FileUtil.readMessageFromFile(testPath);
		Set<Integer> topicIndexSet = new HashSet<Integer>();
		for (Message message : messages)
		{
			String content = message.getContent();
			Document doc = new Document(content);
			testDocs.docs.add(doc);
			topicIndexSet.add(model.predictNewSampleTopic(doc));
		}
		/**
		 * 预测每条短信，得到每条的最大概率主题，最后找到每个最大概率主题的前20个词，集合,计算tf-idf
		 */
		Set<Word> wordSet = model.getWordByTopics(topicIndexSet, 20);
		LDAFeatureProcess.calTFIDFAsWeight(docSet, wordSet);
		return wordSet;
	}

	@Test
	public void test() throws IOException
	{
		String resultPath = "ldaResult/";
		String parameterFile = "source/lda_parameters.txt";
		String trainPathDir = "LDATrain/";
		String testPath = "train/train_messages.txt";
		Set<Word> wordSet = trainAndPredictLDA(trainPathDir, parameterFile, resultPath, testPath);
		FileUtil.writeKeyWordFile("ldaWords/keyWords.doc", new ArrayList<Word>(wordSet));
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException
	{
		// TODO Auto-generated method stub
		String resultPath = "ldaResult/";
		String parameterFile = "source/lda_parameters.txt";

		modelparameters ldaparameters = new modelparameters();
		getParametersFromFile(ldaparameters, parameterFile);
		String dirPath = "LDATrain/";
		Documents docSet = new Documents();
		docSet.readDocs(dirPath);
		System.out.println("wordMap size " + docSet.termToIndexMap.size());
		FileUtil.mkdir(resultPath);
		LdaModel model = new LdaModel(ldaparameters);
		System.out.println("1 Initialize the model ...");
		model.initializeModel(docSet);
		System.out.println("2 Learning and Saving the model ...");
		model.inferenceModel(docSet);
		System.out.println("3 Output the final model ...");
		model.saveIteratedModel(ldaparameters.iteration, docSet);
		System.out.println("Done!");

		// 预测新文本
		String messStr = "好消息！！薇町婚纱造型推出老带新活动啦！已在本店预定的新娘推荐新顾客来本店，定单后即赠送新、老顾客各一支价值58元定妆隔离水（在婚礼当";
		Document doc = new Document(messStr);
		int topicIndex = model.predictNewSampleTopic(doc);
		Set<Word> wordSet = model.getWordByTopic(topicIndex);
		FileUtil.writeKeyWordFile("ldaWords/comparedkeyWords.doc", new ArrayList<Word>(wordSet));
	}

}