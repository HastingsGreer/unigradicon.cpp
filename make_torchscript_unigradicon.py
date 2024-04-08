import unigradicon
import torch

model = unigradicon.get_unigradicon()

example = torch.jit.trace(model, (torch.rand(1, 1, 175, 175, 175).cuda(), torch.rand(1, 1, 175, 175, 175).cuda()))

example.save("traced_unigradicon.pt")

