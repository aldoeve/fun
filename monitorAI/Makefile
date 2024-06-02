OS=$(shell lsb_release -si)

enter:
	@echo "source .venv/bin/activate"

run:
	python3 simpleMonitor.py

setup:
	pip install virtualenv
ifneq ($(OS),Ubuntu)
	@echo $(OS)
else
	sudo apt install python3.10-venv
endif
	python3 -m venv .venv
	touch .gitignore
	echo ".venv/" > .gitignore