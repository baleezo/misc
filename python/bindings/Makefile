all:
		@for i in */Makefile; do\
				make -C $$(dirname $$i) -f Makefile;\
		done


clean:
		@for i in */Makefile; do\
				make -C $$(dirname $$i) -f Makefile clean;\
		done
