#pragma once

#include <utility>
#include "perception/vision/CameraToRR.hpp"
#include "perception/vision/VisionDefs.hpp"
#include "perception/vision/VisionConstants.hpp"
#include "perception/vision/RobotRegion.hpp"
#include "types/FieldFeatureInfo.hpp"
#include "VisionFrame.hpp"
#include "Fovea.hpp"
#include "yuv.hpp"


#include "types/PostInfo.hpp"
#include "utils/Histogram.hpp"

class Vision;

class GoalDetection {
   public:

      typedef Histogram<int, cNUM_COLOURS> XHistogram;
      typedef Histogram<int, cNUM_COLOURS> YHistogram;

      /**
       * Find goals in the image and write the locations to the
       * blackboard
       **/
      void findGoals(
               VisionFrame    &frame,
               std::vector<Point> fEP,
               const Fovea    &fovea, 
               unsigned int   *seed);

      std::vector<PostInfo> posts;
      std::vector<boost::shared_ptr<FoveaT<hGoals, eGrey> > > goalFoveas;
      std::vector<std::vector<Point> >  goalPostLines;

   private:


      void postSearch(const VisionFrame &frame,std::vector<Point> fEP,const Fovea &fovea,
              std::vector<BBox> &regions);


      void performSanityChecks(const Fovea &fovea,
                               const VisionFrame &frame,
                               std::vector<BBox> &regions, bool secondCheck);
      /**
       * Attempts to find other goalpost if only one if initially found
       */
      void  findOther(const Fovea &fovea,
              					  const VisionFrame &frame,
              					  std::vector<BBox> &regions);


      float adjustSize(VisionFrame &frame,
                                       const Fovea& fovea,
                                       BBox& goal,
                                       int numPosts,
                                       PostInfo& p);
      /**
       * Calculates the distance to the post
       * Tunes the BBox as well
       **/
      RRCoord findDistanceToPost(VisionFrame &frame,
                                 const Fovea& fovea,
                                 BBox& goal,
                                 int numPosts,
                                 PostInfo& p,float wdistance);

      /**
       * Calculates the distance to the post using the width
       * If update = true, the BBox is tuned
       **/
      float widthDistanceToPost(VisionFrame &frame,
                                BBox& goal,
                                float height,
                                bool update = false);

      /**
       * Tunes the BBox to more accurately identify the base of the post
       **/
      void findBaseOfPost(VisionFrame &frame,
                          BBox& goal);

      /**
       * Labels posts as left and right
       **/
      PostInfo::Type determineLeftRightPost(const Fovea &fovea,
                                            const std::vector<BBox>& regions,
                                            const BBox& goal,
                                            PostInfo& p);

};

