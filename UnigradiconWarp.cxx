#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkIdentityTransform.h"
#include "itkTransformFileReader.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkLinearInterpolateImageFunction.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {

      std::cerr << "Usage: " << argv[0] << " --fixed <fixed_image> --moving <moving_image> [--transform <transform_file>] --warped_moving_out <output_image> [--nearest_neighbor] [--linear]" << std::endl;
  }
  

  std::string fixedImageFile;
  std::string movingImageFile;
  std::string transformFile;
  std::string outputImageFile;
  bool useNearestNeighbor = false;
  bool useLinear = false;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "--fixed") {
      fixedImageFile = argv[++i];
    } else if (arg == "--moving") {
      movingImageFile = argv[++i];
    } else if (arg == "--transform") {
      transformFile = argv[++i];
    } else if (arg == "--warped_moving_out") {
      outputImageFile = argv[++i];
    } else if (arg == "--nearest_neighbor") {
      useNearestNeighbor = true;
    } else if (arg == "--linear") {
      useLinear = true;
    } else {
      std::cerr << "Usage: " << argv[0] << " --fixed <fixed_image> --moving <moving_image> [--transform <transform_file>] --warped_moving_out <output_image> [--nearest_neighbor] [--linear]" << std::endl;
      return EXIT_FAILURE;
    }
  }

  constexpr unsigned int Dimension = 3;
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer fixedReader = ReaderType::New();
  fixedReader->SetFileName(fixedImageFile);
  fixedReader->Update();
  ImageType::Pointer fixedImage = fixedReader->GetOutput();

  ReaderType::Pointer movingReader = ReaderType::New();
  movingReader->SetFileName(movingImageFile);
  movingReader->Update();
  ImageType::Pointer movingImage = movingReader->GetOutput();

  using TransformType = itk::Transform<double, Dimension, Dimension>;
  TransformType::Pointer transform;

  if (transformFile.empty()) {
    using IdentityTransformType = itk::IdentityTransform<double, Dimension>;
    transform = IdentityTransformType::New();
  } else {
    using TransformReaderType = itk::TransformFileReader;
    TransformReaderType::Pointer transformReader = TransformReaderType::New();
    transformReader->SetFileName(transformFile);
    transformReader->Update();
    transform = dynamic_cast<TransformType*>(transformReader->GetTransformList()->front().GetPointer());
  }

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  ResampleFilterType::Pointer resampleFilter = ResampleFilterType::New();
  resampleFilter->SetInput(movingImage);
  resampleFilter->SetTransform(transform);
  resampleFilter->SetUseReferenceImage(true);
  resampleFilter->SetReferenceImage(fixedImage);

  if (useLinear) {
    using LinearInterpolatorType = itk::LinearInterpolateImageFunction<ImageType, double>;
    resampleFilter->SetInterpolator(LinearInterpolatorType::New());
  } else if (useNearestNeighbor) {
    using NearestNeighborInterpolatorType = itk::NearestNeighborInterpolateImageFunction<ImageType, double>;
    resampleFilter->SetInterpolator(NearestNeighborInterpolatorType::New());
  } else {
    std::cerr << "Specify --nearest_neighbor or --linear" << std::endl;
    return EXIT_FAILURE;
  }

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputImageFile);
  writer->SetInput(resampleFilter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
