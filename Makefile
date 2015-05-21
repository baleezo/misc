%_only:
		make -C `echo $(@) | sed 's/_only\$$//g'` -f Makefile

%_clean:
		make -C `echo $(@) | sed 's/_clean\$$//g'` -f Makefile clean

all:
		@for i in */Makefile; do\
				make -C $$(dirname $$i) -f Makefile;\
		done

clean:
		@for i in */Makefile; do\
				make -C $$(dirname $$i) -f Makefile clean;\
		done
