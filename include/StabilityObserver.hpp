#pragma once

enum class StabilityLevel {
    Normal,
    Warning,
    Critical
};

class StabilityObserver {
public:
    virtual ~StabilityObserver() = default;

    // Apelat de Subject cand nivelul de stabilitate isi schimba categoria
    virtual void onStabilityChanged(float stability, StabilityLevel level) = 0;
};