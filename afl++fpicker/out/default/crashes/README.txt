Command line used to find this crash:

./afl-fuzz -m none -i in -o out -- /data/local/tmp/afl++fpicker/fpicker/fpicker -v --fuzzer-mode afl -e attach -p test -f /data/local/tmp/afl++fpicker/fpicker/examples/test/fuzzer-agent.js --communication=send

If you can't reproduce a bug outside of afl-fuzz, be sure to set the same
memory limit. The limit used for this fuzzing session was 0 B.

Need a tool to minimize test cases before investigating the crashes or sending
them to a vendor? Check out the afl-tmin that comes with the fuzzer!

Found any cool bugs in open-source tools using afl-fuzz? If yes, please drop
an mail at <afl-users@googlegroups.com> once the issues are fixed

  https://github.com/AFLplusplus/AFLplusplus

