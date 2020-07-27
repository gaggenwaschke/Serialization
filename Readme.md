# Serialization

This library supplies generic classes for (reflection like) description of classes, 
their members and function and serialization.

## Benchmark

A few benchmark with different settings are made.
They are made to give a general idea of performance and not
created in a proper environment at all.

Old Benchmarks
Commit | comment | optimization flags | number of runs | time/µs | binary size/kBytes
-|-|-|-|-|-
68b311433f3cdcce37a94a2362fd22652193617c | | -Og -g | 1e7 | 11772837 | 435,0
68b311433f3cdcce37a94a2362fd22652193617c | | -Ofast | 1e7 | 9516451 | 35,7
68b311433f3cdcce37a94a2362fd22652193617c | | -Os | 1e7 | 11239371 | 25,7
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Og -g | 1e7 | 9057969 | 435,0
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Ofast | 1e7 | 6845635 | 35,7
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Os | 1e7 | 8264227 | 25,7

New Becnhmarks:
Commit | comment | optimization flags | serializations | iterations | avg time/µs | std deviation/µs | binary size/kBytes
-|-|-|-|-|-|-|-
f887eb477ffcc0f88899834c9fcc4395670e9e45 | old status with new benchmark | -Og -g | 1e5 | 1e2 | 89596 | 3505 | 443,9
f887eb477ffcc0f88899834c9fcc4395670e9e45 | old status with new benchmark | -Ofast | 1e5 | 1e2 | 68563 | 1134 | 35,7
f887eb477ffcc0f88899834c9fcc4395670e9e45 | old status with new benchmark | -Os | 1e5 | 1e2 | 82808 | 3076 | 25,8
