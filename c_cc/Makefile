all:
		@for i in */Makefile; do\
				make --directory=$$(dirname $$i) --file=Makefile;\
		done


clean:
		@for i in */Makefile; do\
				make --directory=$$(dirname $$i) --file=Makefile clean;\
		done
