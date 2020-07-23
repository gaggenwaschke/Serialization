# Serialization

This library supplies generic classes for (reflection like) description of classes, 
their members and function and serialization.

## Benchmark

A few benchmark with different settings are made.
They are made to give a general idea of performance and not
created in a proper environment at all.

Commit | comment |optimization flags | number of runs | time/µs | binary size/kBytes
-|-|-|-|-|-
68b311433f3cdcce37a94a2362fd22652193617c | | -Og -g | 1e7 | 11772837 | 435,0
68b311433f3cdcce37a94a2362fd22652193617c | | -Ofast -g | 1e7 | 9516451 | 35,7
68b311433f3cdcce37a94a2362fd22652193617c | | -Os -g | 1e7 | 11239371 | 25,7
