UVa ACM-ICPC Binder
=================

This repository is forked from the Stanford ACM-ICPC teams.
It currently hosts 
- The team notebook with algrothm templates and classical problems [notebook.pdf](notebook.pdf)
- Theoretical Computer Science Cheat Sheet [cheat_sheet.pdf](cheat_sheet.pdf)
- The complete lecture slides for [CS 97SI](http://stanford.edu/class/cs97si/) under [97si_slides/](97si_slides/) folder. 

*Much of this notebook is compiled from codes written by previous Stanford team members and coaches.*

Generating team notebook
========================
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents of the notebook from `contents.txt`.


``` bash
### Script for generating the PDF file
python3 generate_pdf.py 

### Script for generating the HTML file 
python3 generate_html.py
``` 

Edit the index in [contents.txt](contents.txt) to include more content

PDF version
-----------
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.

HTML version
------------
Requires: [Python 2/3](https://www.python.org/), [enscript](https://www.gnu.org/software/enscript/)

Syntax highlighting is handled solely by enscript, and in order to change the color schemes, either the default options of enscript or `generate_html.py` should be edited accordingly.
