OS=$(shell lsb_release -si)

enter:
	@echo "source translator/bin/activate"

run:
	python3 translator.py

enviromentReqs:
	pip3 install -r requirements.txt

setup:
	pip install virtualenv
ifneq ($(OS),Ubuntu)
	@echo $(OS)
else
	sudo apt install python3.10-venv
endif
	python3 -m venv translator
	touch .gitignore
	echo "translator/" > .gitignore