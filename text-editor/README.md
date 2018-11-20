# Text editor

## TODO
1. Modeling in the code
2. Parsing document json → document object
3. Rendering
4. Editing/Updating
5. Basic Styles
6. Grid support
7. Export to PDF/ODT/HTML

## Details

### Modeling in the code
Header
Footer
Title 1 – 6
Paragraph
Ordered/UnorderedList
Image url
Grid
Code
Quote
Text

// embed

config:
tabSize: “2”

style:
font-size
font-style: “bold|italic|normal”
font-family
color
underlined: “color size”
align: “left|center|right”
justify: “true|false”
line-spacing: “size”
indent: “2”

Every element can take style but grid
	style

Style spread into their children

→
JSON
XML

press key →
	update the view → html|canvas|string|docx|odt
	update the tree













{
	config: {
	},
	root: {
		style: {
			fontSize: 12
		},
		type: “paragraph”,
		child: [
			“id-generated” : {
				order: 0,
				style: {
					fontSize: 14
				}
				type: “Text”,
				content: “test”
			}
		]
	}
}

Text tdonobevvsvavsdvsdvsdd bdfbd fbsbsnoinsdnvsdvds dsdsvsnionvsdo


[html] | [document object]

document object can be rendered in separated thread


