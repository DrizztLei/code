<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	            version="1.0">
	<xsl:output method="html"
                doctype-system="about:legacy-compat"
                indent="yes"
                encoding="UTF-8" />
	<xsl:template match="/">
		<html>
			<head>
				<title>Technical Certification Exam Tool</title>
			</head>
			<body>
				<form action="/ILSCS01/ExamForm" method="post">
					<table>
						<tbody>
							<tr>
								<td align="center"
									bgcolor="lightblue">
									<h2>
										Exam ID:
										<xsl:value-of
											select="/test/@id" />
										-
										<xsl:value-of
											select="/test/description" />
										<br />
									</h2>
								</td>
							</tr>
							<xsl:apply-templates select="//question" />
						</tbody>
					</table>
				</form>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="question">
		<tr>
			<td>
				<xsl:value-of select='@id' />
				)
				<xsl:value-of select='questionText' />
				<hr />
				<xsl:apply-templates select='choices/choice' />
				<tr>
					<td bgcolor="lightblue">
						<xsl:if test='choices/@allowMultiple="Yes"'>
							Multiple Select Question - Please
							select all correct answers.
						</xsl:if>
						<xsl:if test='choices/@allowMultiple="No"'>
							Single Select Question - Please select
							the best answer.
						</xsl:if>
					</td>
				</tr>
			</td>
		</tr>

	</xsl:template>

	<xsl:template match="choice">
		<xsl:variable name="typeVariable">
			<xsl:choose>
				<xsl:when test='../@allowMultiple="No"'>radio</xsl:when>
				<xsl:otherwise>checkbox</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<input type="{$typeVariable}" name="{../../@id}" value="{@id}" />

		<xsl:value-of select='@id' />
		.
		<xsl:value-of disable-output-escaping='yes' select='choiceText' />

		<br />
	</xsl:template>
</xsl:stylesheet>
