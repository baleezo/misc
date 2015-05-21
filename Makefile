%_only:
		make --directory=`echo $(@) | sed 's/_only//g'` --file=Makefile

%_clean:
		make --directory=`echo $(@) | sed 's/_clean//g'` --file=Makefile clean

all:
		@for i in */Makefile; do\
				make --directory=$$(dirname $$i) --file=Makefile;\
		done


clean:
		@for i in */Makefile; do\
				make --directory=$$(dirname $$i) --file=Makefile clean;\
		done
