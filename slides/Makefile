
MARKDOWN_SLIDES=$(wildcard *.md)

reveal.js:
	git clone https://github.com/hakimel/reveal.js.git
	cd reveal.js && npm install

reveal_start: reveal.js
	cd reveal.js && npm start &
	touch reveal_running
	sleep 5

reveal_running: reveal_start

reveal_stop:
	-pkill grunt
	-rm reveal_running

reveal_slides: $(subst .md,.html,$(MARKDOWN_SLIDES))

pdf_slides: $(subst .md,.pdf,$(MARKDOWN_SLIDES))

%.reveal: reveal.js %.html
	cp -r $(dir $(basename $@))/* reveal.js/
	cp $*.html reveal.js/index.html

%.pdf: %.reveal reveal_running
	chromium-browser http://localhost:8000/?print-pdf&pdfSeparateFragments=false

%.html: %.md to_reveal.py
	python3 to_reveal.py $< >$@
