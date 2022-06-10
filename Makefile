SUBDIRS:=libsakk main

all clean:
	@for subdir in $(SUBDIRS); do $(MAKE) -C $$subdir $@; done

test:
	$(MAKE) -C libsakk $@

.PHONY: all clean test
