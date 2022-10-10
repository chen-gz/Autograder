import os
for i in range(258):
    with open(f"file{i}.txt", "w") as f:
        f.write(f"{i}")
