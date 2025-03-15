/*
Copyright (C) 2025 ChenPi11.
This file is part of chenpi11-blog.

chenpi11-blog is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

chenpi11-blog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>. */

package chenpi11_blog

import (
	"os"
	"strings"

	"github.com/gookit/color"
	"github.com/leonelquinteros/gotext"
	"golang.org/x/net/html"
)

var tabMap map[string]string

// Rendering <tab-div-page>'s content.
func renderingTabDivPageContent(node *html.Node, htmlPath string) {
	if node.Type == html.ElementNode && node.Data == "tab-div-page" {
		for _, attr := range node.Attr {
			if attr.Key == "name" {
				color.Info.Printf(gotext.Get("Rendering tab-div-page '%s' in '%s' ...\n"), attr.Val, htmlPath)
				tabDivPageContent := node.FirstChild
				if tabDivPageContent == nil {
					color.Warn.Printf(gotext.Get("<tab-div-page> '%s' in '%s' has no content.\n"), attr.Val, htmlPath)
					continue
				}
				renderedContent := MarkdownIt(tabDivPageContent.Data)
				tabTag := "@RENDERED_" + attr.Val + "@"
				node.FirstChild = &html.Node{
					Type: html.TextNode,
					Data: tabTag,
				}
				tabMap[tabTag] = renderedContent
			}
		}
	}

	for c := node.FirstChild; c != nil; c = c.NextSibling {
		renderingTabDivPageContent(c, htmlPath)
	}
}

// Save the modified HTML file.
func saveHTMLFile(node *html.Node, htmlPath string) {
	// Open the HTML file for writing.
	htmlFile, err := os.Create(htmlPath)
	if err != nil {
		color.Error.Printf(gotext.Get("Error while creating HTML file: %v\n"), err)
		return
	}
	defer htmlFile.Close()

	tempIOWriter := strings.Builder{}

	// Write the modified HTML content to the file.
	err = html.Render(&tempIOWriter, node)

	if err != nil {
		color.Error.Printf(gotext.Get("Error rendering HTML: %s\n"), err)
		return
	}

	// Replace tab tags.
	htmlContent := tempIOWriter.String()
	for tabTag, tabContent := range tabMap {
		htmlContent = strings.ReplaceAll(htmlContent, tabTag, tabContent)
	}
	_, err = htmlFile.WriteString(htmlContent)
	if err != nil {
		color.Error.Printf(gotext.Get("Error writing HTML file: %s\n"), err)
		return
	}
}

// Rendering tab-div-page in HTML file.
func RenderingTabOfHTMLFile(htmlPath string) {
	// Open the HTML file.
	htmlFile, err := os.Open(htmlPath)
	if err != nil {
		color.Error.Printf(gotext.Get("Error opening HTML file: %s\n"), err)
		return
	}
	defer htmlFile.Close()

	tabMap = make(map[string]string)

	// Parse the HTML file.
	htmlDoc, err := html.Parse(htmlFile)
	if err != nil {
		color.Error.Printf(gotext.Get("Error parsing HTML file: %s\n"), err)
		return
	}

	// Rendering tab-div-page.
	renderingTabDivPageContent(htmlDoc, htmlPath)

	// Save the modified HTML file.
	saveHTMLFile(htmlDoc, htmlPath)
}
