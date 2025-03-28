#######################################
#시간에 따른 충돌량 그래프
#######################################

import pandas as pd
import matplotlib.pyplot as plt

# 충돌 로그 데이터 불러오기
df = pd.read_csv("/home/woojin/Desktop/project/qos/result.csv")

# collision == 1 인 로그만 필터링
collisions = df[df["collision"] == 1]

# 시간별 충돌 횟수 집계
collisions_by_time = collisions.groupby("time").size().reset_index(name="collision_count")

# 플롯 그리기
plt.figure(figsize=(12, 6))
plt.plot(collisions_by_time["time"], collisions_by_time["collision_count"], 'r.-', label="Collisions")

plt.title("Number of Collisions Over Time")
plt.xlabel("Time (s)")
plt.ylabel("Collision Count")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("/home/woojin/Desktop/project/plot/collisions_plot.png")

