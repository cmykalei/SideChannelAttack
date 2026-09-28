#!/bin/sh

REMOTE=/home/ke131/Assignments/compx304-a4
SSH_ALIAS=lab
SRC=src
OUT=build
LOG=log

build_local() {
    make build
}

build_remote() {
    scp Makefile $SSH_ALIAS:$REMOTE/
    scp -r $SRC $SSH_ALIAS:$REMOTE/
    ssh $SSH_ALIAS << EOF
        cd $REMOTE
        make build
EOF
    scp $SSH_ALIAS:$REMOTE/$OUT/* $OUT/
}

run_local() {
    runs=$1
    i=1
    while [ $i -le "$runs" ]; do
        make run
        i=$((i + 1))
    done
}

run_remote() {
    scp Makefile $SSH_ALIAS:$REMOTE/
    runs=$1
    ssh $SSH_ALIAS << EOF
        cd $REMOTE
        i=1
        while [ \$i -le $runs ]; do
            make run
            i=\$((i + 1))
        done
EOF
    scp $SSH_ALIAS:$REMOTE/$LOG/*.md $LOG/
}

clean_local() {
    make clean
}

clean_remote() {
    scp Makefile $SSH_ALIAS:$REMOTE/
    ssh $SSH_ALIAS << EOF
        cd $REMOTE
        make clean
EOF
}

reset_local() {
    make reset
}

reset_remote() {
    scp Makefile $SSH_ALIAS:$REMOTE/
    ssh $SSH_ALIAS << EOF
        cd $REMOTE
        make reset
EOF
}

arg=$1
case $arg in
    "build"|"clean"|"reset")
        case $2 in
             "remote")
                 ${arg}_remote ;;
             *)
                ${arg}_local ;;
         esac ;;
    ''|*[!0-9]*)
         printf "Usage 1: ./run.sh <runs> [optional 'remote']\n"
         printf "Usage 2: ./run.sh build [optional 'remote']\n"
         exit 1 ;;
    *)
        if [ "$arg" -ge 1 ] && [ "$arg" -le 50 ]; then
            case $2 in
             "remote")
                  run_remote $arg ;;
             *)
                 run_local $arg ;;
            esac
        else
            printf "Runs must be between 1-50 inclusive!\n"
            printf "Usage 1: ./run.sh <runs> [optional 'remote']\n"
            printf "Usage 2: ./run.sh build [optional 'remote']\n"
            exit 1
        fi ;;
esac
