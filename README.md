# 🔢 Numerical Methods for Nonlinear Equations (C++)

> Comparative implementation of classical root-finding algorithms  
> Developed as part of a Numerical Methods laboratory project.

---

## 📌 Overview

This project implements and compares multiple **numerical methods** for solving nonlinear equations (algebraic and transcendental).

The goal is to:

- Detect intervals containing roots
- Apply multiple numerical algorithms
- Compare convergence speed and numerical behavior
- Analyze computational complexity and stability

The program automatically runs all methods on two equations and prints a structured comparative table.

---

## 🧮 Implemented Methods

| Method | Type | Convergence | Derivative Required |
|--------|------|-------------|--------------------|
| Bisection | Bracketing | Linear | ❌ No |
| Fixed-Point Iteration | Iterative | Linear (if |φ'(x)| < 1) | ❌ No |
| Newton's Method | Tangent-based | Quadratic | ✅ Yes |
| Secant Method | Quasi-Newton | Superlinear (~1.618) | ❌ No |

---

## 📘 Problems Solved

### 🔹 Problem A
\[
\sqrt{x+1} - \frac{1}{x} = 0
\]

- Transcendental equation
- Interval analyzed: `[0.1, 5.0]`
- Fixed-point transformation used

---

### 🔹 Problem B
\[
x^3 + 34x + 23 = 0
\]

- Cubic algebraic equation
- Interval analyzed: `[-5.0, 5.0]`
- Monotonic derivative (ensures unique root)

---

## ⚙️ Program Workflow

For each equation:

1. **Root Separation**
   - Scans interval using step size `0.5`
   - Detects sign changes

2. **Bisection (ε = 10⁻²)**
   - Provides stable initial approximation

3. **High Precision Methods (ε = 10⁻⁶)**
   - Fixed-Point Iteration
   - Newton
   - Secant

4. **Comparative Table Output**
   - Approximated root
   - f(root)
   - Iteration count

---

## 📊 Convergence Analysis

### 1️⃣ Bisection Method
- Order of convergence: **Linear**
- Error after n iterations:
\[
E_n \leq \frac{b-a}{2^n}
\]
- Iterations required:
\[
n \approx \log_2\left(\frac{b-a}{\varepsilon}\right)
\]

✔ Always converges if sign change exists  
❌ Slower compared to derivative-based methods  

---

### 2️⃣ Fixed-Point Iteration
- Convergence condition:
\[
|\phi'(x)| < 1
\]
- Order: **Linear**
- Sensitive to choice of transformation φ(x)

✔ Simple implementation  
❌ May diverge if poorly chosen  

---

### 3️⃣ Newton’s Method
- Order of convergence: **Quadratic**
- Error relation:
\[
E_{n+1} \approx C E_n^2
\]

✔ Very fast convergence near root  
✔ Typically requires fewer iterations  
❌ Requires derivative  
❌ Sensitive to bad initial guess  

---

### 4️⃣ Secant Method
- Order: **Superlinear**
\[
\approx 1.618
\]
- Does not require derivative
- Approximates derivative numerically

✔ Faster than fixed-point  
✔ No explicit derivative needed  
❌ Less stable than Newton  

---

## ⏱ Computational Complexity

Let:
- n = number of iterations
- T(f) = cost of evaluating function
- T(df) = cost of evaluating derivative

| Method | Time Complexity |
|--------|-----------------|
| Bisection | O(n) |
| Fixed-Point | O(n) |
| Newton | O(n) (with derivative cost) |
| Secant | O(n) |

However, due to different convergence rates:

- Newton → smallest n
- Secant → medium n
- Fixed-point → larger n
- Bisection → predictable but slow

In practice:
Quadratic convergence dramatically reduces iteration count.

---

## 🧠 Numerical Stability Considerations

The implementation includes safeguards:

- Derivative near zero detection (Newton)
- Division by zero protection (Secant)
- Maximum iteration cap (10,000)
- Precision thresholds

These ensure safe termination and prevent infinite loops.

---

## 🖥️ Compilation & Execution

### Linux / macOS
```bash
g++ -std=c++11 -O2 main.cpp -o numerical_methods
./numerical_methods
Windows (MinGW)
g++ -std=c++11 -O2 main.cpp -o numerical_methods.exe
numerical_methods.exe
📁 Project Structure
main.cpp
README.md

Single-file implementation focused on algorithm clarity and comparison.

🎯 Learning Outcomes

This project demonstrates:

Numerical root-finding theory

Convergence order comparison

Stability vs speed trade-offs

Practical implementation in C++

Error tolerance analysis (10⁻² vs 10⁻⁶ precision)

🚀 Possible Improvements

Add graphical convergence visualization

Export results to CSV

Add automatic convergence rate measurement
[MN Lab1 Chiochiu Vladislav.docx](https://github.com/user-attachments/files/25716760/MN.Lab1.Chiochiu.Vladislav.docx)







