package backstage;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import lda.Main;

@WebServlet(name = "Manager", value = "/findTopic")
public class Manager extends HttpServlet
{
	private static final long serialVersionUID = 1L;
	private String charset = "UTF-8";
	private final String HEADCONTENT = "text/html;charset=UTF-8";
	// private final int HEADSIZE = HEADCONTENT.length();
	private final int TOPICSIZE = 20;
	private final int DOCUMENTSIZE = 40;
	private final int FILELIMIT = 5;

	static
	{
		try
		{
			Main.main(null);
			System.out.println("TRAIN DONE ! ");
		}
		catch (IOException e)
		{ // TODO Auto-generated catch block
			System.out.println("ERROR IN PARSE THE MODEL");
			e.printStackTrace();
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.servlet.http.HttpServlet#doGet(javax.servlet.http.
	 * HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	@Override

	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
	{
		doPost(req, resp);
	}

	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
	{
		request.setCharacterEncoding(charset);
		response.setCharacterEncoding(charset);

		PrintWriter pw = response.getWriter();
		response.setContentType(HEADCONTENT);
		// Map<String, String[]> params = request.getParameterMap();

		String content = "", html = "", type = "";

		final int topicHash = "topic".hashCode();
		final int fileHash = "file".hashCode();
		final int showHash = "show".hashCode();
		final int docHash = "doc".hashCode();

		type = request.getParameter("group");
		content = request.getParameter("content");

		if (type != null && type.length() != 0)
		{
			type = type.trim();
			if(content != null)
			{
				content = content.trim();
			}
			int typeHash = type.hashCode();
			if (typeHash == topicHash)
			{
				html += sendTopic(pw, content, response);
			}
			else if (typeHash == fileHash)
			{
				html += sendDocument(pw, content, response);

			}
			else if (typeHash == docHash)
			{
				html += generateDocumentHTML(content);
			}
			else if (typeHash == showHash)
			{
				html += sendAllTopic(pw, response);
			}
		}

		System.out.println("HTML : ");
		System.out.println(html);

		pw.println(html);

		pw.flush();
		pw.close();

	}

	public String sendTopic(PrintWriter pw, String topic, HttpServletResponse response)
	{
		LinkedList<String> topicSet = Main.topicFindTopic(topic);
		String returntTopic = "";

		for (int i = 0; i < topicSet.size(); i++)
		{
			returntTopic += topicSet.get(i) + "\n";
		}

		return returntTopic;
	}

	public String sendDocument(PrintWriter pw, String topic, HttpServletResponse response)
	{
		LinkedList<String> documentSet = Main.topicFindFile(topic);
		String returnFile = "";

		for (int i = 0; i < documentSet.size(); i++)
		{
			returnFile += documentSet.get(i) + "\n";
		}

		return returnFile;
	}

	public String sendAllTopic(PrintWriter pw, HttpServletResponse response)
	{
		String set = "";
		for (int i = 0; i < Main.info.length; i++)
		{
			for (int j = 0; j < Main.info[i].length; j++)
			{
				set += Main.info[i][j][0] + "\t";
			}
			set += "\n";
		}
		return set;
	}

	public String sendAllDocument(PrintWriter pw, String fileName)
	{
		LinkedList<String> documentSet = Main.fileFindFIle(fileName);

		String returnFile = "";

		for (int i = 0; i < documentSet.size(); i++)
		{
			returnFile += documentSet.get(i) + "\n";
		}

		return returnFile;
	}

	public String generateNode(int id, int category, String name, String label, int symbolSize, boolean ignore,
			boolean flag)
	{
		String node = "{";
		node += "id:" + id + ",";
		node += "category:" + category + ",";
		node += "name:" + "'" + name + "'" + ",";
		node += "label:" + "'" + label + "'" + ",";
		node += "symbolSize:" + symbolSize + ",";
		node += "ignore:" + ignore + ",";
		node += "flag:" + flag;
		node += "},";
		return node;
	}

	public String generateLinks(int source, int target)
	{
		String links = "{";
		links += "source:" + source + ",";
		links += "target:" + target;
		links += "},";
		return links;
	}

	public String generateCategory(String name)
	{
		String category = "{";
		category += "name:" + "'" + name + "'";
		category += "},";
		return category;
	}

	public String generateHTMLHead()
	{
		String html = "";
		html += "<!DOCTYPE html>" + "<html>" + "<head>" + "<meta charset='UTF-8'>" + "<title>TopicDoc</title>"
				+ "</head>" + "<body>" + "<div id='main' style='width:850px;height:500px'>" + "</div>"
				+ "<script src='http://echarts.baidu.com/build/dist/echarts.js'>" + "</script>"
				+ "<script type='text/javascript'>" + "require.config(" + "{"
				+ "paths:{echarts:'http://echarts.baidu.com/build/dist'}" + "});"
				+ "require(['echarts','echarts/chart/force']," + "function(ec){"
				+ "var myChart=ec.init(document.getElementById('main'));" + "var option={" + "tooltip:"
				+ "{show:false}," + "series:[{" + "type:'force'," + "name:'Forcetree'," + "itemStyle:{" + "normal:{"
				+ "label:{" + "show:true}," + "nodeStyle:{" + "brushType:'both',"
				+ "borderColor:'rgba(255,215,0,0.4)',borderWidth:1" + "}" + "}" + "}" + ",	";
		return html;
	}

	public String generateHTMLEnd()
	{
		String html = "";
		html += "	}" + "]" + "};" + "myChart.setOption(option);" + "var ecConfig=require('echarts/config');"
				+ "myChart.setOption(option);" + "myChart.on(ecConfig.EVENT.CLICK,ecConfig);" + "myChart.show();"
				+ "});" + "</script>" + "</body>" + "</html>";
		return html;
	}

	public String generateDocumentHTML(String content)
	{
		System.out.println("FIND DOCUMENT CLUSTER TO " + content);
		String html = "", categories = "", nodes = "", links = "";

		LinkedList<String> fileFindTopic = Main.fileFindTopic(content);

		html += generateHTMLHead();

		categories += "categories:[";
		categories += generateCategory("topic");
		categories += generateCategory("doc");
		categories += "],";

		nodes += "nodes:[";
		links += "links:[";

		int count = 0;
		int preTopic = 0;
		for (int i = 0; i < fileFindTopic.size(); i++)
		{
			String topic = fileFindTopic.get(i);
			nodes += generateNode(count, 0, "" + count, topic, TOPICSIZE, false, true);
			LinkedList<String> topicFindFile = Main.topicFindFile(topic);
			links += generateLinks(preTopic, count);
			int topicID = count;
			preTopic = topicID;
			count++;
			for (int j = 0; j < topicFindFile.size() && j < FILELIMIT; j++)
			{
				String fileName = topicFindFile.get(j);
				nodes += generateNode(count, 1, "" + count, fileName, DOCUMENTSIZE, false, true);
				links += generateLinks(topicID, count);
				count++;
			}
		}

		nodes += "],";
		links += "]";

		html += categories;
		html += nodes;
		html += links;

		html += generateHTMLEnd();

		return html;
	}
}
