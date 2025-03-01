# 导入库和模块
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
import torchvision.utils as vutils
import os


# 定义生成器
class Generator(nn.Module):
    def __init__(self):
        super(Generator, self).__init__()
        self.main = nn.Sequential(
            nn.Linear(100, 256),
            nn.ReLU(),
            nn.Linear(256, 512),
            nn.ReLU(),
            nn.Linear(512, 1024),
            nn.ReLU(),
            nn.Linear(1024, 3 * 96 * 96),
            nn.Tanh()
        )

    def forward(self, x):
        return self.main(x).view(-1, 3, 96, 96)


# 定义判别器
class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()
        self.main = nn.Sequential(
            nn.Linear(3 * 96 * 96, 1024),
            nn.ReLU(),
            nn.Linear(1024, 512),
            nn.ReLU(),
            nn.Linear(512, 256),
            nn.ReLU(),
            nn.Linear(256, 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        x = x.view(-1, 3 * 96 * 96)
        return self.main(x)


# 数据预处理
transform = transforms.Compose([
    transforms.Resize((96, 96)),
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))
])

# 加载数据集
dataset = datasets.ImageFolder(r"D:\@Code\deepLearning\dataSets\faces", transform=transform)
dataloader = DataLoader(dataset, batch_size=64, shuffle=True)

# 检查是否有可用的GPU，如果有则使用GPU，否则使用CPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 初始化模型、损失函数和优化器
generator = Generator().to(device)
discriminator = Discriminator().to(device)
criterion = nn.BCELoss()
optimizer_G = optim.Adam(generator.parameters(), lr=0.0002, betas=(0.5, 0.999))
optimizer_D = optim.Adam(discriminator.parameters(), lr=0.0002, betas=(0.5, 0.999))

# 训练GAN
num_epochs = 1000
batch_size = 64
save_interval = 100

for epoch in range(num_epochs):
    for i, (images, _) in enumerate(dataloader):
        # 训练判别器
        real_labels = torch.ones(images.size(0), 1).to(device)
        fake_labels = torch.zeros(images.size(0), 1).to(device)

        # 计算真实图像的损失
        real_outputs = discriminator(images.to(device))
        real_loss = criterion(real_outputs, real_labels)

        # 生成假图像并计算损失
        z = torch.randn(images.size(0), 100).to(device)
        fake_images = generator(z)
        fake_outputs = discriminator(fake_images.detach())
        fake_loss = criterion(fake_outputs, fake_labels)

        # 更新判别器权重
        d_loss = real_loss + fake_loss
        optimizer_D.zero_grad()
        d_loss.backward()
        optimizer_D.step()

        # 计算生成器的损失
        z = torch.randn(images.size(0), 100).to(device)
        fake_images = generator(z)
        fake_outputs = discriminator(fake_images)
        g_loss = criterion(fake_outputs, real_labels)

        # 更新生成器权重
        optimizer_G.zero_grad()
        g_loss.backward()
        optimizer_G.step()

    print(f"Epoch [{epoch + 1}/{num_epochs}], D_loss: {d_loss.item():.4f}, G_loss: {g_loss.item():.4f}")

    # 生成照片并保存
    if (epoch + 1) % save_interval == 0:
        with torch.no_grad():
            z = torch.randn(batch_size, 100).to(device)
            generated_images = generator(z).detach().cpu()

        save_path = f"generated_images_epoch_{epoch + 1}"
        os.makedirs(save_path, exist_ok=True)

        for i in range(generated_images.size(0)):
            vutils.save_image(generated_images[i], os.path.join(save_path, f"generated_{i + 1}.png"))

        print(f"Generated images saved in '{save_path}' folder.")
