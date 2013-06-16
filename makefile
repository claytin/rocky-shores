ifndef config
  config=debug
endif
export config

all:

clean:
	@echo Cleaning up horrible mess
	@echo Oh by the way this doesn't do anything... yey...

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"