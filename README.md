# Side Channel Attacks
The final report is in [Report.md](Report.md) and relevant evidence can be found in [log/](log/).

![Summary](summary.png)

## Project 🌳
```
.
├── Makefile
├── README.md
├── Report.md
├── build
│   └── main
├── cache_hits.png
├── cpu_cycles.png
├── log
├── run.sh
├── src
│   ├── config.h
│   ├── main.c
│   ├── mem.c
│   ├── mem.h
│   ├── probe.c
│   ├── probe.h
│   ├── utils.c
│   └── utils.h
└── summary.png
```

### Usage
All source code is documented with doxygen style comments. I didn't actually generate it but I find that it's helpful to read in code anyway.

**The headers contain all the relevant documentation** and so I've avoided commenting in the C code (apart from in main for obvious reasons) to keep it clean.

The output goes to [log/](log/) in a file called `run-<date>.md`, either as markdown tables or CSV depending on the `print_` function in [src/main.c](src/main.c).

## Commands
1. To build and run use `make build` and `make run` on the lab machines.
2. Alternatively use `./run.sh build remote` and `./run.sh 10 remote`.
3. Use `./run.sh <1-50>` on the lab machines to run multiple tests.
