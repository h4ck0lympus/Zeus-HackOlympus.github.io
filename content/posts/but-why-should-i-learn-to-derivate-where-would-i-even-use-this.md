---
title: "\"But why should I learn derivatives? Where would I even use this?\""
date: 2026-06-03
draft: false
math: true
---

I am going through Andrej Karpathy's Zero to Hero neural network series[1], and right now I am at the micrograd video.

This post is mostly a note to myself, and also an appreciation of the kind of math we often learn in college without really seeing where it becomes useful. I want to explain backpropagation in my own words so I understand it properly, instead of just following the video and nodding along.

Writing things down this way helps me notice the parts that are still fuzzy. If I cannot explain a step clearly, then I probably do not understand it well enough yet.

Alongside writing this post, I am also implementing micrograd in Rust. That gives me two feedback loops at once:

1. explain the idea in plain words
2. implement the idea in code

By doing both, I am not only learning backpropagation, but also getting more comfortable with Rust.

## Why derivatives matter here

When people first learn derivatives, the usual question is:

> "But why should I learn derivatives? Where would I even use them?"

Backpropagation is one of the clearest answers.

If a neural network makes a bad prediction, we need a way to measure how each parameter contributed to that error. Derivatives give us exactly that. They tell us how much a small change in one value affects another value.

That is the core idea behind gradient descent and backpropagation:

1. compute the output
2. measure the error
3. figure out how each intermediate value affected that error
4. update the parameters in the direction that reduces it

In the rest of this post, I want to build that intuition from a very small computation graph before thinking about a full neural network.

At a very low level, a neural network is just a very large equation. For this example, we can start with a much smaller one:

\[
L = (a \cdot b + c) \cdot f
\]

Now we can break it into smaller intermediate steps:

\[
e = a \cdot b
\]

\[
d = e + c
\]

\[
L = d \cdot f
\]

This is nicer to think about because each line becomes one small operation in the computation graph.

If we want to represent it as a DAG (or computation graph):

<!-- ![Compuation Graph](/images/computation_graph.jpeg)  -->
{{< diagram path="/images/graph.svg" alt="Computation graph for L = (a * b + c) * f" wide="true" >}}


From multivariable calculus, the gradient is the rate of change of the final output \(L\) with respect to each input.

For this tiny graph, that means we care about quantities like:

\[
\frac{\partial L}{\partial a}, \frac{\partial L}{\partial b}, \frac{\partial L}{\partial c}, \frac{\partial L}{\partial f}
\]

As I said before, a derivative tells us how a change in one value affects another value. Here, we want to know how changing one input changes the final output \(L\).

Because this equation has multiple inputs, we use partial derivatives. A partial derivative tells us how the output changes when we vary one input while keeping the others fixed.

So, for example, \(\frac{\partial L}{\partial a}\) tells us how sensitive \(L\) is to changes in \(a\), and \(\frac{\partial L}{\partial c}\) tells us how sensitive \(L\) is to changes in \(c\).

The gradient is just all of those partial derivatives grouped together into one vector:

\[
\nabla L =
\left[
\frac{\partial L}{\partial a},
\frac{\partial L}{\partial b},
\frac{\partial L}{\partial c},
\frac{\partial L}{\partial f}
\right]
\]

That vector tells us how each input contributes to the final result. Backpropagation is the process of computing those gradients efficiently by moving backward through the computation graph.

During gradient descent, we update a variable by moving in the opposite direction of its gradient. In other words, if we want to reduce the final output \(L\), we follow the negative gradient direction.

### Backpropagation

Coming back to our equation, we have:

\[
L = (a \cdot b + c) \cdot f
\]

\[
e = a \cdot b
\]

\[
d = e + c
\]

\[
L = d \cdot f
\]

Now we want to compute the derivative of \(L\) with respect to each intermediate value and input. We do that by moving backward, from the final output \(L\) to the original inputs \(a\), \(b\), \(c\), and \(f\).

We start with the easiest one:

\[
\frac{\partial L}{\partial L} = 1
\]

This just says that if \(L\) changes a little, then \(L\) changes by exactly that same amount.

Next, look at the last operation:

\[
L = d \cdot f
\]

If we differentiate \(L\) with respect to \(d\), we get:

\[
\frac{\partial L}{\partial d} = \frac{\partial}{\partial d}(d \cdot f) = f
\]

Similarly, if we differentiate \(L\) with respect to \(f\), we get:

\[
\frac{\partial L}{\partial f} = \frac{\partial}{\partial f}(d \cdot f) = d
\]

So this last multiplication node already tells us something important: the gradient (rate of change) flowing into \(d\) is scaled by \(f\), and the gradient flowing into \(f\) is scaled by \(d\).

Now let us move one layer deeper.

We want to know:

\[
\frac{\partial L}{\partial e} = ?
\]

At this point, we already know how changes in \(d\) affect \(L\):

\[
\frac{\partial L}{\partial d}
\]

We also know that:

\[
d = e + c
\]

So if we can measure how a change in \(e\) affects \(d\), then we can combine that with how a change in \(d\) affects \(L\). That is exactly where the chain rule comes in.

This is also the point where the math starts to feel more natural instead of just symbolic. We are not doing magic here. We are just breaking one difficult dependency into two simpler ones.

Instead of asking directly, "How does \(e\) affect \(L\)?", we can break the question into two smaller ones:

\[
\text{How does } e \text{ affect } d?
\]

\[
\text{How does } d \text{ affect } L?
\]

Multiply those two effects together, and we get how \(e\) affects \(L\).

As put by George F. Simmons:

> "If a car travels twice as fast as a bicycle and the bicycle is four times as fast as a walking man, then the car travels 2 × 4 = 8 times as fast as the man."

That is the same intuition here. If \(e\) affects \(d\), and \(d\) affects \(L\), then \(e\) affects \(L\) through \(d\).

More formally, the chain rule here is:

$$
\begin{aligned}
\frac{\partial L}{\partial e}
&=
\frac{\partial L}{\partial d}
\cdot
\frac{\partial d}{\partial e}
\end{aligned}
$$

Now look at the local operation:

\[
d = e + c
\]

If we differentiate \(d\) with respect to \(e\), we get:

\[
\frac{\partial d}{\partial e} = 1
\]

because increasing \(e\) by a small amount increases \(d\) by the same amount.

So:

$$
\begin{aligned}
\frac{\partial L}{\partial e}
&=
\frac{\partial L}{\partial d}
\cdot
\frac{\partial d}{\partial e} \\
&=
\frac{\partial L}{\partial d} \cdot 1 \\
&=
\frac{\partial L}{\partial d}
\end{aligned}
$$

The same idea applies to \(c\):

\[
\frac{\partial d}{\partial c} = 1
\]

which means:

$$
\begin{aligned}
\frac{\partial L}{\partial c}
&=
\frac{\partial L}{\partial d}
\cdot
\frac{\partial d}{\partial c} \\
&=
\frac{\partial L}{\partial d}
\end{aligned}
$$

So the addition node passes the gradient backward unchanged to both \(e\) and \(c\).

Now we can move one step further back to:

\[
e = a \cdot b
\]

Just like before, we use the chain rule again.

To compute how \(a\) affects \(L\), we write:

$$
\begin{aligned}
\frac{\partial L}{\partial a}
&=
\frac{\partial L}{\partial e}
\cdot
\frac{\partial e}{\partial a}
\end{aligned}
$$

Since:

\[
\frac{\partial e}{\partial a} = b
\]

we get:

$$
\begin{aligned}
\frac{\partial L}{\partial a}
&=
\frac{\partial L}{\partial e}
\cdot b
\end{aligned}
$$

Similarly, for \(b\):

$$
\begin{aligned}
\frac{\partial L}{\partial b}
&=
\frac{\partial L}{\partial e}
\cdot
\frac{\partial e}{\partial b}
\end{aligned}
$$

and since:

\[
\frac{\partial e}{\partial b} = a
\]

we get:

$$
\begin{aligned}
\frac{\partial L}{\partial b}
&=
\frac{\partial L}{\partial e}
\cdot a
\end{aligned}
$$

So the multiplication node passes gradients backward in a very simple way: each side gets the upstream gradient multiplied by the value of the other side.

That is really the heart of backpropagation. At each node, we do not need to re-derive the whole giant expression from scratch. We only need two things:

1. the gradient flowing into the current node
2. the local derivative of that node's operation

Then the chain rule lets us combine them and move one step backward.

When a neural network gets large, the graph becomes much bigger, but the idea stays the same. Backpropagation is just the repeated application of local derivatives and the chain rule across the computation graph.

That is why derivatives matter so much here. They are not just abstract things from a calculus class. They are the tool that tells a model how to learn.

<br>

For me, the best way to make this feel real was to pair the math with code. I built a small Rust version of `micrograd` alongside this post, and it helped expose the parts I only thought I understood.
Repo: [micrograd-rs](https://github.com/h4ck0lympus/micrograd-rs)

#### *References:*

* [Andrej Karpathy's Zero to Hero neural network series](https://youtu.be/VMj-3S1tku0?si=hcl-W6zRnK2vfSk5)
* [3b1b's Neural Network playlist](https://youtube.com/playlist?list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&si=Fq0_n_wWmtI8IW4I)
* [Chain rule Wikipedia](https://en.wikipedia.org/wiki/Chain_rule)
