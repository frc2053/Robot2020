#pragma once

class MockToF {
 public:
  enum Status {
    kValid,
    kSigmaHigh,
    kReturnSignalLow,
    kReturnPhaseBad,
    kHardwareFaliure,
    kWrappedTarget,
    kInternalError,
    kInvalid
  };
  enum RangingMode {
    kShort,
    kMedium,
    kLong
  };
  MockToF(int port);
  void IdentifySensor();
  int GetFirmwareVersion() const;
  int GetSerialNumber() const;
  bool IsRangeValid() const;
  double GetRange() const;
  double GetRangeSigma() const;
  double GetAmbientLightLevel() const;
  Status GetStatus() const;
  void SetRangingMode(RangingMode mode);
  void SetRangeOfInterest(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
private:
  int portNum;
  int tlX;
  int tlY;
  int brX;
  int brY;
  RangingMode currentMode;
};
