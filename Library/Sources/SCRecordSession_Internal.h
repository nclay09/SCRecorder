//
//  SCRecordSession_Internal.h
//  SCRecorder
//
//  Created by Simon CORSIN on 24/11/14.
//  Copyright (c) 2014 rFlex. All rights reserved.
//

#import "SCRecorder.h"
#import "SCRecordSession.h"

@interface SCRecordSession() {
    AVAssetWriter *_assetWriter;
    AVAssetWriterInput *_videoInput;
    AVAssetWriterInput *_audioInput;
    NSMutableArray *_segments;
    NSMutableArray *_recordSegmentsFirstFramePresentationTime;
    BOOL _audioInitializationFailed;
    BOOL _videoInitializationFailed;
    BOOL _recordSegmentReady;
    BOOL _currentSegmentHasVideo;
    BOOL _currentSegmentHasAudio;
    
    int _currentSegmentCount;
    CMTime _timeOffset;
    CMTime _lastTimeAudio;
    CMTime _currentSegmentDuration;
    CMTime _sessionStartTime;
    
    SCVideoConfiguration *_videoConfiguration;
    SCAudioConfiguration *_audioConfiguration;
    
    AVAssetWriterInputPixelBufferAdaptor *_videoPixelBufferAdaptor;
    CMTime _lastTimeVideo;
    
    dispatch_queue_t _audioQueue;
    
    // Used when the fastRecordMethod is enabled
    AVCaptureMovieFileOutput *_movieFileOutput;
}

@property (weak, nonatomic) SCRecorder *recorder;

@property (readonly, nonatomic) BOOL videoInitialized;
@property (readonly, nonatomic) BOOL audioInitialized;
@property (readonly, nonatomic) BOOL videoInitializationFailed;
@property (readonly, nonatomic) BOOL audioInitializationFailed;
@property (readonly, nonatomic) BOOL recordSegmentReady;
@property (readonly, nonatomic) BOOL currentSegmentHasAudio;
@property (readonly, nonatomic) BOOL currentSegmentHasVideo;
@property (readonly, nonatomic) BOOL isUsingMovieFileOutput;
@property (nonatomic) CMTime currentSegmentFirstFramePresentationTime;

- (void)initializeVideo:(NSDictionary *)videoOptions formatDescription:(CMFormatDescriptionRef)formatDescription error:(NSError **)error;
- (void)initializeAudio:(NSDictionary *)audioOptions formatDescription:(CMFormatDescriptionRef)formatDescription error:(NSError **)error;

- (CVPixelBufferRef)createPixelBuffer;

- (void)appendVideoPixelBuffer:(CVPixelBufferRef)videoSampleBuffer atTime:(CMTime)time duration:(CMTime)duration completion:(void(^)(BOOL success))completion;

- (void)appendAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer completion:(void(^)(BOOL success))completion;


- (void)beginRecordSegmentUsingMovieFileOutput:(AVCaptureMovieFileOutput *)movieFileOutput error:(NSError **)error delegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;

- (void)notifyMovieFileOutputIsReady;

- (void)appendRecordSegmentUrl:(NSURL *)url info:(NSDictionary *)info initialPresentationTime:(CMTime)initialPresentationTime error:(NSError *)error completionHandler:(void (^)(SCRecordSessionSegment *, NSError *))completionHandler;

- (void)appendRecordSegment:(void(^)(NSInteger segmentNumber, NSError* error))completionHandler error:(NSError *)error url:(NSURL *)url initialPresentationTime:(CMTime)initialPresentationTime  duration:(CMTime)duration;

@end
