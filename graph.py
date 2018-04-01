import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

style.use('fivethirtyeight')

fig = plt.figure()
axis = fig.add_subplot(1, 1, 1)

def animate(i):
    with open('data.txt', 'r') as f:
        graph_data = f.read().split('\n')
        xs = []
        ys = []
        zs = []
        time = []
        for data in graph_data:
            try:
                x, y, z, idx = map(int, data.split(' '))
            except ValueError:
                continue
            xs.append(x)
            ys.append(y)
            zs.append(z)
            time.append(idx)

        axis.clear()
        axis.plot(time, xs, time, ys, time, zs)

ani = animation.FuncAnimation(fig, animate, interval=250)
plt.show()
