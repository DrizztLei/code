from sklearn.manifold import TSNE
from sklearn.datasets import load_iris
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

iris = load_iris()

"""
X_tsne = TSNE(learning_rate=10).fit_transform(iris.data)

# X_pca = PCA().fit_transform(iris.data)

plt.figure(figsize=(10, 5))
plt.subplot(121)
plt.scatter(X_tsne[:, 0], X_tsne[:, 1], c=iris.target)
# plt.subplot(122)
# plt.scatter(X_pca[:, 0], X_pca[:, 1], c=iris.target)

plt.show()

"""

data = iris.data

feature_0 = data[::, 0]
feature_1 = data[::, 1]
feature_2 = data[::, 2]
feature_3 = data[::, 3]

label = iris.target

t_sne = TSNE(learning_rate=0.001)

out = t_sne.fit_transform(iris.data)

