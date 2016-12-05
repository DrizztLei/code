<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
    <xsl:output method="html"
                doctype-system="about:legacy-compat"
                encoding="UTF-8"
                indent="yes"/>
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
                                <td align="center" bgcolor="lightblue">
                                    <h2>
                                        Exam ID:
                                        <xsl:value-of select="/test/@id"/>
                                        -
                                        <xsl:value-of select="/test/description"/>
                                        <br/>
                                    </h2>
                                </td>
                            </tr>
                            <xsl:apply-templates select="//question"/>
                        </tbody>
                    </table>
                </form>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="question">
        <tr>
            <td>
                <xsl:value-of select='@id'/>
                )
                <xsl:value-of select='questionText'/>
                <hr/>
                <tr>
                    <td bgcolor="lightblue">
                    </td>
                </tr>
            </td>
        </tr>

    </xsl:template>

</xsl:stylesheet>
