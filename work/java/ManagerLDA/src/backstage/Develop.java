package backstage;

import java.util.LinkedList;

import lda.Main;

public class Develop
{
	public static void main(String[] args)
	{
		Develop develop = new Develop();
		String html = "";
		html += develop.generateHTMLHead();

		html += "categories:[";

		html += develop.generateCategory("topic");
		html += develop.generateCategory("doc");

		html += "],";

		html += "nodes:[";
		html += develop.generateNode(0, 0, "0", "develop", "40", false, false);
		html += develop.generateNode(1, 1, "name", "label", "40", false, false);
		html += "],";

		html += "links:[";
		html += develop.generateLinks(0, 1);
		html += "]";

		html += develop.generateHTMLEnd();
		System.out.println(html);
	}

	public String generateNode(int id, int category, String name, String label, String symbolSize, boolean ignore,
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
		links += "target:" + target ;
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

	public String generageDocumentHTML(String document)
	{
		String html = "";
		html += generateHTMLHead();

		html += "categories:[";
		html += "],";

		html += "node:[";
		html += "],";

		html += "links:[";
		html += "]";

		LinkedList<String> info = Main.fileFindFIle(document);

		for (int i = 0; i < info.size(); i++)
		{
			html += info.get(i);
		}

		html += generateHTMLEnd();
		return html;
	}
}
