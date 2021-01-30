NPROCS=16


.PHONY: clean fsm gui flash simulator

clean:
	make -f gcc/Makefile clean -j$(NPROCS)

gui:
	make -f gcc/Makefile -j$(NPROCS)

flash:
	make -f gcc/Makefile flash -j$(NPROCS)

simulator:
	make -f TouchGFX/simulator/gcc/Makefile -j$(NPROCS)
	./TouchGFX/build/bin/simulator.exe
