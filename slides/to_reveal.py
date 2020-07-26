#!/usr/bin/env python3

import sys
import logging
logging.getLogger().setLevel(logging.INFO)
filename = sys.argv[1]

slide_title = None
style = None
with open(filename, 'r', encoding='utf-8') as f:
	lines = f.read().splitlines(keepends=False)
	def line_with(start):
		try:
			line = next(
				filter(lambda line: line.startswith(start), lines)
			)
			return line.partition(":")[2].strip()
		except StopIteration:
			return None
	slide_title = line_with("title: ")
	style = line_with("style: ")

print("""<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">

		<title>{}</title>

		<link rel="stylesheet" href="css/reveal.css">
		<link rel="stylesheet" href="css/theme/{style}">

		<!-- Theme used for syntax highlighting of code -->
		<link rel="stylesheet" href="lib/css/zenburn.css">

		<!-- Printing and PDF exports -->
		<script>
			var link = document.createElement( 'link' );
			link.rel = 'stylesheet';
			link.type = 'text/css';
			link.href = window.location.search.match( /print-pdf/gi ) ? 'css/print/pdf.css' : 'css/print/paper.css';
			document.getElementsByTagName( 'head' )[0].appendChild( link );
		</script>
	</head>
	<body>
		<div class="reveal">
			<div class="slides">
""".format(slide_title, style=style or "black.css"))
logging.info("selected style {}".format(style))

import pathlib
print("""
	<section data-markdown="{}"
		data-separator="^---"
		data-separator-vertical="^--"
	>
	</section>
	""".format(pathlib.Path(filename).parts[-1])
)

print("""
			</div>
		</div>

		<script src="lib/js/head.min.js"></script>
		<script src="js/reveal.js"></script>

		<script>
			// More info about config & dependencies:
			// - https://github.com/hakimel/reveal.js#configuration
			// - https://github.com/hakimel/reveal.js#dependencies
			Reveal.initialize({
				slideNumber: true,
				history: true,
				margin: 0.05,
				dependencies: [
					{ src: 'plugin/markdown/marked.js' },
					{ src: 'plugin/markdown/markdown.js' },
					{ src: 'plugin/notes/notes.js', async: true },
					{ src: 'plugin/highlight/highlight.js', async: true, callback: function() { hljs.initHighlightingOnLoad(); } }
				]
			});
		</script>
	</body>
</html>
""")